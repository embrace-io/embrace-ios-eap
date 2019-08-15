#!/bin/bash

# min search depth to use when looking for frameworks. expose this as an envvar to allow modification in an Xcode build phase.
EMBRACE_DSYM_SEARCH_DEPTH=3
# set this value to suppress warnings about needing to upload dSYMs manually when Bitcode is enabled
DISABLE_BITCODE_CHECK=

function log () {
    # xcode will mark log lines as warnings and errors if prefixed with the values below. the prefixes are removed and error and warning markers replace them.
    case $2 in
      warning)
        prefix="warning: "
        ;;
      error)
        prefix="error: "
        ;;
      *)
        prefix=""
        ;;
    esac

    echo "${prefix}[Embrace dSYM Upload] $(date +"%Y/%m/%d %H:%M:%S") $1"
}


function log_error () {
    log "$1" "error"
}


function log_warning () {
    log "$1" "warning"
}


function run() {
    if [ -z "$EMBRACE_DEBUG_DSYM" ] ; then
        # we must redirect both stdout and stderr to /dev/null to have Xcode run this script in the background and move on to other build tasks
        eval $1 > /dev/null 2>&1 &
    else
        log "running upload command: $1"
        eval $1
    fi
}


function upload() {
    cd "$BUILD_ROOT"

    # if we can't find the files we are looking for with globs, we want nulls
    shopt -s nullglob

    # XCode should provide these environment variables, but other CI setups may not provide them
    if [ -n "$DWARF_DSYM_FILE_NAME" -a -n "$DWARF_DSYM_FOLDER_PATH" ] ; then
        app_dsym_path="${DWARF_DSYM_FOLDER_PATH}/${DWARF_DSYM_FILE_NAME}/Contents/Resources/DWARF/"
    else
        log "DWARF_DSYM_FILE_NAME and/or DWARF_DSYM_FOLDER_PATH envvars not defined. Attempting to find dSYM file using glob." "warning"
        app_dsym_path=*/*.dSYM/*/Resources/DWARF/
    fi

    log "Looking for app dSYM in $app_dsym_path"

    # Xcode will sometimes not have completed the GenerateDSYMFile step before it runs the upload script, so we allow
    # for a small delay to occur before continuing
    tries=4
    found=
    for try in {1..4} ; do
        app_dsym_file=$(find "$app_dsym_path" -type f)
        [ -n "$app_dsym_file" -a -e "$app_dsym_file" ] && found=1 && break
        sleep 0.5
    done

    if [ -n "$found" ] ; then
        icon=$(echo "$PWD"/*/*.xcassets/AppIcon.appiconset/Icon-60@2x.png | head -n 1)
        if [ -n "$icon" ] ; then
          icon_arg="-icon $icon"
        else
          icon_arg=""
        fi

        run "\"$DIR\"/upload -app $EMBRACE_ID -token $EMBRACE_TOKEN $icon_arg \"$app_dsym_file\""
    else
        log_warning "No app dSYM file was found under BUILD_ROOT ${BUILD_ROOT}. Skipping upload."
    fi

    # use `find` and a for loop to build up the list of dSYMs rather than a glob so we can properly handle escaping of spaces
    framework_dsyms=$(find . -mindepth $EMBRACE_DSYM_SEARCH_DEPTH -name "*.dSYM")
    if [ -n "$framework_dsyms" ] ; then
        ORIG_IFS=$IFS
        IFS=$'\n'
        dsym_args=""
        for dsym in $framework_dsyms ; do
            dsym_full_path="$(find "${dsym}"/Contents/Resources/DWARF/*  -type f 2>/dev/null)"
            if [ -z "$dsym_full_path" ] ; then
                continue
            fi
            dsym_args="$dsym_args \"$dsym_full_path\""
        done
        IFS=$ORIG_IFS
        run "\"$DIR\"/upload -app $EMBRACE_ID -token $EMBRACE_TOKEN $dsym_args"
    fi
}


run_msg="Running"
if [ -n "$EMBRACE_DEBUG_DSYM" ] ; then
    run_msg="$run_msg in debug mode"
    unset EMBRACE_USE_SYSLOG
else
    export EMBRACE_USE_SYSLOG=1
fi
log "$run_msg"

if [ "$ENABLE_BITCODE" = "YES" -a -z "$DISABLE_BITCODE_CHECK" ] ; then
    log "\"Enable bitcode\" is set to \"YES\". You will need to download dSYMs from Apple for TestFlight and App Store builds and then upload those dSYMs to Embrace."
fi

DIR=$(cd "$(dirname "$0")" && pwd -P)

if [ -z "$EMBRACE_ID" ]
then
  log_error "Missing EMBRACE_ID environment variable. Skipping upload."
  exit 1
fi

if [ -z "$EMBRACE_TOKEN" ]
then
  log_error "Missing EMBRACE_TOKEN environment variable. Skipping upload."
  exit 1
fi

log "Using app ID ${EMBRACE_ID} and API token ${EMBRACE_TOKEN}"

if [ -z "$BUILD_ROOT" ]
then
  log_error "Missing BUILD_ROOT environment variable. Are you running this from a build step in XCode? Skipping upload."
  exit 1
fi

# if we have data about the configured debug format, use it. we may not have this setting though if we are running in certain CI environments, so do not exit if it is not set.
if [ -n "$DEBUG_INFORMATION_FORMAT" ] ; then
    if [ "$DEBUG_INFORMATION_FORMAT" != "dwarf-with-dsym" ] ; then
        log_warning "DEBUG_INFORMATION_FORMAT set to '$DEBUG_INFORMATION_FORMAT'. Skipping upload. Set it to 'dwarf-with-dsym' to generate a dSYM for your application"
        exit 0
    fi
fi

upload &
