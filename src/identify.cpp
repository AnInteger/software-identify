#include "identify.h"

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

// #include <archive.h>
// #include <archive_entry.h>

using namespace software::identify;

// https://www.debian.org/doc/debian-policy/ch-controlfields.html

enum Keywords {
    Package,
    Status,
    Architecture,
    Version,
    Depends,
    Description,
    Maintainer,
    Section,
    Priority,
    Homepage,
    Original_Maintainer,
    Installed_Size,
    Pre_Depends,
    Recommends,
    Suggests,
    Conflicts,
    Breaks,
    Replaces,
    Conffiles,
    Config_Version
};

static std::map<unsigned int, std::string> ENUM_STRING = {
    {Package, "Package"}, // 包名
    {Status, "Status"}, // 安装状态
    {Architecture, "Architecture"}, // 架构
    {Version, "Version"}, // 版本
    {Depends, "Depends"}, // 依赖
    {Description, "Description"}, // 描述
    {Maintainer, "Maintainer"}, // 厂商
    {Section, "Section"}, // 存档位置，分离
    {Priority, "Priority"}, // 优先级
    {Homepage, "Homepage"}, // 主页
    {Original_Maintainer, "Original-Maintainer"}, // 原始维护者
    {Installed_Size, "Installed-Size"}, // 安装大小
    {Pre_Depends, "Pre-Depends"}, // 预依赖
    {Recommends, "Recommends"}, // 推荐依赖
    {Suggests, "Suggests"}, // 建议依赖
    {Conflicts, "Conflicts"}, // 冲突
    {Breaks, "Breaks"}, // 破坏
    {Replaces, "Replaces"}, // 可替换项
    {Conffiles, "Conffiles"}, // 配置文件
    {Config_Version, "Config-Version"} // 配置版本
};

static std::map<std::string, unsigned int> STRING_ENUM = {
    {"Package", Package}, // 包名
    {"Status", Status}, // 安装状态
    {"Architecture", Architecture}, // 架构
    {"Version", Version}, // 版本
    {"Replaces", Replaces}, // 可替换项
    {"Depends", Depends}, // 依赖
    {"Description", Description}, // 描述
    {"Maintainer", Maintainer}, // 厂商
    {"Section", Section}, // 存档位置，分离
    {"Priority", Priority}, // 优先级
    {"Homepage", Homepage}, // 主页
    {"Original-Maintainer", Original_Maintainer}, // 原始维护者
    {"Installed-Size", Installed_Size}, // 安装大小
    {"Pre-Depends", Pre_Depends}, // 预依赖
    {"Recommends", Recommends}, // 推荐依赖
    {"Suggests", Suggests}, // 建议依赖
    {"Conflicts", Conflicts}, // 冲突
    {"Breaks", Breaks}, // 破坏
    {"Conffiles", Conffiles}, // 配置文件
    {"Config-Version", Config_Version} // 配置版本
};

static // 提取 .deb 文件中的 control.tar.gz
bool extractControlTarGz(const std::string &debPath, const std::string &outputDir) {
    // struct archive *a = archive_read_new();
    // struct archive_entry *entry = nullptr;
    // int ret;

    // // 支持 .deb (ar 格式) 和 tar.gz
    // archive_read_support_format_ar(a);
    // archive_read_support_format_tar(a);
    // archive_read_support_filter_gzip(a);

    // // 打开 .deb 文件
    // if ((ret = archive_read_open_filename(a, debPath.c_str(), 10240)) != ARCHIVE_OK) {
    //     std::cerr << "Error opening .deb file: " << archive_error_string(a) << std::endl;
    //     archive_read_free(a);
    //     return false;
    // }

    // // 遍历 .deb 内部文件
    // bool found = false;
    // while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
    //     std::string filename = archive_entry_pathname(entry);

    //     // 找到 control.tar.gz
    //     if (filename == "control.tar.gz") {
    //         found = true;
    //         std::string outputPath = outputDir + "/control.tar.gz";

    //         // 写入 control.tar.gz 到磁盘
    //         std::ofstream outFile(outputPath, std::ios::binary);
    //         if (!outFile.is_open()) {
    //             std::cerr << "Failed to create output file: " << outputPath << std::endl;
    //             break;
    //         }

    //         // 逐块读取并写入文件
    //         const void *buff;
    //         size_t size;
    //         int64_t offset;
    //         while (archive_read_data_block(a, &buff, &size, &offset) == ARCHIVE_OK) {
    //             outFile.write(static_cast<const char*>(buff), size);
    //         }
    //         outFile.close();
    //         std::cout << "Extracted: " << outputPath << std::endl;

    //         // 解压 control.tar.gz
    //         struct archive *tar = archive_read_new();
    //         archive_read_support_format_tar(tar);
    //         archive_read_support_filter_gzip(tar);

    //         if (archive_read_open_filename(tar, outputPath.c_str(), 10240) != ARCHIVE_OK) {
    //             std::cerr << "Failed to open control.tar.gz" << std::endl;
    //             break;
    //         }

    //         // 提取 control.tar.gz 的内容
    //         while (archive_read_next_header(tar, &entry) == ARCHIVE_OK) {
    //             std::string innerFile = archive_entry_pathname(entry);
    //             std::string innerPath = outputDir + "/" + innerFile;

    //             // 跳过目录（仅处理文件）
    //             if (archive_entry_filetype(entry) == AE_IFDIR) {
    //                 continue;
    //             }

    //             // 写入文件
    //             std::ofstream innerOut(innerPath, std::ios::binary);
    //             if (!innerOut.is_open()) {
    //                 std::cerr << "Failed to create file: " << innerPath << std::endl;
    //                 continue;
    //             }

    //             // 逐块读取并写入
    //             while (archive_read_data_block(tar, &buff, &size, &offset) == ARCHIVE_OK) {
    //                 innerOut.write(static_cast<const char*>(buff), size);
    //             }
    //             innerOut.close();
    //             std::cout << "Extracted: " << innerPath << std::endl;
    //         }

    //         archive_read_close(tar);
    //         archive_read_free(tar);
    //         break;
    //     }
    // }

    // archive_read_close(a);
    // archive_read_free(a);

    // if (!found) {
    //     std::cerr << "control.tar.gz not found in the .deb file!" << std::endl;
    //     return false;
    // }

    return true;
}

void SoftwareIdentify::IdentifyOneByPath(const std::string& pkgpath) {
    
};

inline std::string TrimLeft(std::string& line) {
    size_t pos = line.find_first_of(':');
    if (pos != std::string::npos)
        return line.substr(line.find_first_of(':') + 2);
    return line;
}

inline bool startsWith(const std::string& s, const std::string& sub) {	
    return s.find(sub) == 0 ? true : false;
}

inline bool endswith(const std::string& s, const std::string& sub) {
	return (s.rfind(sub) != -1) && (s.rfind(sub) == (s.length() - sub.length()) ? true : false);
}

static std::string beginWithKeywords(const std::string& str) {
    if (str.empty()) return "";
    for (auto& keyword : STRING_ENUM) {
        if (startsWith(str, keyword.first)) {
            return keyword.first;
        }
    }
    return "";
}

Soft SoftwareIdentify::IdentifyOneByName(const std::string& pkgname) {
    // TODO 跨运行支持
    std::ifstream file("/var/lib/dpkg/status");
    if (!file) {
        std::cout << "open file err! " << std::endl;
        return nullptr;
    }

    std::string full = "Package: " + pkgname;
    std::string buff;
    std::vector<std::string> lines;
    while(getline(file, buff)) {
        if (buff != full) continue;
        lines.push_back(buff);
        while(getline(file, buff)) {
            if (buff.empty()) break;
            lines.push_back(buff);
        }
        break;
    }
    file.close();

    if (lines.empty()) return nullptr;

    std::shared_ptr<SoftwareInfo> soft = std::make_shared<SoftwareInfo>();
    for (size_t i = 0; i < lines.size(); i++) {
        std::string section_name = beginWithKeywords(lines[i]);
        std::string content;
        if (!section_name.empty()) {
            content += TrimLeft(lines[i]);
            i++;
            while (i < lines.size() && beginWithKeywords(lines[i]).empty()) {
                content += lines[i];
                i++;
            }
            i--;
        } else {
            continue;
        }

        section_name += ": ";
        // std::cout << section_name << content << std::endl;
        if (startsWith(section_name, "Package: ")) {
            soft->Package = content;
        } else if (startsWith(section_name, "Section: ")) {
            soft->Section = content;
        } else if (startsWith(section_name, "Installed-Size: ")) {
            soft->Installed_Size = content;
        } else if (startsWith(section_name, "Maintainer: ")) {
            soft->Maintainer = content;
        } else if (startsWith(section_name, "Version: ")) {
            soft->Version = content;
        } else if (startsWith(section_name, "Description: ")) {
            soft->Description = content;
        } else if (startsWith(section_name, "Homepage: ")) {
            soft->Homepage = content;
        }
    }
    return soft;
}


bool isUserSoftWare(const std::string& pkgname) {
    std::string list = "/var/lib/dpkg/info/" + pkgname + ".list";

    std::ifstream file(list);
    if (!file) {
        return false;
    }

    std::string buff;
    std::vector<std::string> lists;
    while (getline(file, buff)) {
        if (endswith(buff, ".desktop")) lists.push_back(buff);
    }

    if (lists.empty()) return false;

    for (auto& list : lists) {
        std::ifstream file(list);
        if (!file) continue;
        std::string buff;
        while (getline(file, buff)) {
            
        }
    }
}
