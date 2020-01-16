Pod::Spec.new do |s|

  s.name                  = "EmbraceIO-EAP"
  s.version               = "4.1.5-EAP"
  s.summary               = "Visibility into your users that you didn't have before"
  s.description           = <<-DESC
                            Embrace is the only performance monitoring platform focused solely on mobile. We are built
                            for the entire mobile team to assure the stability and performance of their apps.
                           DESC

  s.homepage              = "http://embrace.io"
  s.license               = { :type => "Commercial", :text => "Copyright 2018 Embrace.io" }
  s.author                = "Embrace.io"
  s.documentation_url     = "https://docs.embrace.io"

  s.platform              = :ios, "8.0"
  s.source                = { :git => "https://github.com/embrace-io/embrace-ios-eap.git" }
  s.source_files          = "Embrace.framework/Headers/*.h"
  s.public_header_files   = "Embrace.framework/Headers/*.h"
  s.vendored_frameworks   = ["Embrace.framework"]
  s.preserve_paths        = ["run.sh", "upload"]
  s.requires_arc          = true
  s.module_name           = 'EmbraceIO'

end
