Pod::Spec.new do |s|

  s.name                  = "EmbraceIO-EAP"
  s.version               = "5.1.0"
  s.summary               = "Visibility into your users that you didn't have before"
  s.description           = <<-DESC
                            Embrace is the only performance monitoring platform focused solely on mobile. We are built
                            for the entire mobile team to assure the stability and performance of their apps.
                           DESC

  s.homepage              = "http://embrace.io"
  s.license               = { :type => "Commercial", :text => "Copyright 2018 Embrace.io" }
  s.author                = "Embrace.io"
  s.documentation_url     = "https://docs.embrace.io"
  s.source                = { :git => "https://github.com/embrace-io/embrace-ios-eap.git" }
  s.preserve_paths        = ["run.sh", "upload"]
  s.requires_arc          = true
  s.module_name           = 'EmbraceIO'
  
  s.ios.deployment_target     = '8.0'
  s.ios.source_files          = "iOS/Embrace.framework/Headers/*.h"
  s.ios.public_header_files   = "iOS/Embrace.framework/Headers/*.h"
  s.ios.vendored_frameworks   = "iOS/Embrace.framework"
  s.tvos.deployment_target    = '9.0'
  s.tvos.source_files         = "tvOS/Embrace.framework/Headers/*.h"
  s.tvos.public_header_files  = "tvOS/Embrace.framework/Headers/*.h"
  s.tvos.vendored_frameworks  = "tvOS/Embrace.framework"
end
