#pragma once

#include <string>
#include <memory>

namespace software
{
    namespace identify
    {
        class SoftwareInfo {
        public:
            using String = std::string;
            String Package;
            String Installed_Size;
            String Version;
            String Maintainer;
            String Section;
            String Description;
            String Homepage;
        };
        /**
         * 软件识别工具
         * 通过解析软件包的内容，解析出软件的基本信息
         * 支持Deb、Rpm包格式
         * 支持Linux系统
        */

        using Soft = std::shared_ptr<SoftwareInfo>;
        class SoftwareIdentify
        {
        public:
            ~SoftwareIdentify() = default;

            /**
             * 将安装包解压到临时目录，解析软件信息
            */
            void IdentifyOneByPath(const std::string& pkgpath);
            Soft IdentifyOneByName(const std::string& pkgname);
        };
    } // namespace identify
    
} // namespace software
