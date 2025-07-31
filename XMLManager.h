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
    // �R���X�g���N�^
    XMLManager();
    XMLManager(const std::string& filePath);
    
    // �t�@�C���p�X�Ǘ�
    void setFilePath(const std::string& filePath) { this->filePath = filePath; }
    const std::string& getFilePath() const { return filePath; }
    
    // XML�t�@�C������
    bool saveToXML(const std::vector<Project>& projects);
    bool loadFromXML(std::vector<Project>& projects);
    bool validateXML(const std::string& xmlContent);
    
    // �v���W�F�N�g�P�̂̑���
    bool saveProjectToXML(const Project& project, const std::string& fileName);
    bool loadProjectFromXML(Project& project, const std::string& fileName);
    
    // �o�b�N�A�b�v�@�\
    bool createBackup();
    bool restoreFromBackup(const std::string& backupFileName);
    
    // �G�N�X�|�[�g�@�\
    bool exportToCustomFormat(const std::vector<Project>& projects, const std::string& format);
    
    // ���[�e�B���e�B���\�b�h
    std::string escapeXML(const std::string& text);
    std::string unescapeXML(const std::string& xmlText);
    bool fileExists(const std::string& fileName);
    
private:
    // �v���C�x�[�g�w���p�[���\�b�h
    std::string generateProjectsXML(const std::vector<Project>& projects);
    bool parseProjectsXML(const std::string& xmlContent, std::vector<Project>& projects);
    std::string getCurrentTimestamp();
    std::string getBackupFileName();
};