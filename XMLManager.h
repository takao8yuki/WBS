#pragma once
#include <string>
#include <vector>
#include "Project.h"

class XMLManager {
private:
    std::string filePath;
    static const std::string XML_VERSION_HEADER;
    static const std::string ROOT_ELEMENT_START;
    static const std::string ROOT_ELEMENT_END;

public:
    // コンストラクタ
    XMLManager();
    XMLManager(const std::string& filePath);
    
    // ファイルパス管理
    void setFilePath(const std::string& filePath) { this->filePath = filePath; }
    const std::string& getFilePath() const { return filePath; }
    
    // XMLファイル操作
    bool saveToXML(const std::vector<Project>& projects);
    bool loadFromXML(std::vector<Project>& projects);
    bool validateXML(const std::string& xmlContent);
    
    // プロジェクト単体の操作
    bool saveProjectToXML(const Project& project, const std::string& fileName);
    bool loadProjectFromXML(Project& project, const std::string& fileName);
    
    // バックアップ機能
    bool createBackup();
    bool restoreFromBackup(const std::string& backupFileName);
    
    // エクスポート機能
    bool exportToCustomFormat(const std::vector<Project>& projects, const std::string& format);
    
    // ユーティリティメソッド
    std::string escapeXML(const std::string& text);
    std::string unescapeXML(const std::string& xmlText);
    bool fileExists(const std::string& fileName);
    
private:
    // プライベートヘルパーメソッド
    std::string generateProjectsXML(const std::vector<Project>& projects);
    bool parseProjectsXML(const std::string& xmlContent, std::vector<Project>& projects);
    std::string getCurrentTimestamp();
    std::string getBackupFileName();
};