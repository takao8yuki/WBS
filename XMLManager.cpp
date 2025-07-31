#include "XMLManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

// �ÓI�����o�[�̒�`
const std::string XMLManager::XML_VERSION_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
const std::string XMLManager::ROOT_ELEMENT_START = "<wbs_projects>";
const std::string XMLManager::ROOT_ELEMENT_END = "</wbs_projects>";

// �f�t�H���g�R���X�g���N�^
XMLManager::XMLManager() : filePath("wbs_data.xml") {
}

// �t�@�C���p�X�w��R���X�g���N�^
XMLManager::XMLManager(const std::string& filePath) : filePath(filePath) {
}

// �v���W�F�N�g��XML�t�@�C���ɕۑ�
bool XMLManager::saveToXML(const std::vector<Project>& projects) {
    try {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            return false;
        }
        
        std::string xmlContent = generateProjectsXML(projects);
        file << xmlContent;
        file.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving to XML: " << e.what() << std::endl;
        return false;
    }
}

// XML�t�@�C������v���W�F�N�g��ǂݍ���
bool XMLManager::loadFromXML(std::vector<Project>& projects) {
    try {
        if (!fileExists(filePath)) {
            return false;
        }
        
        std::ifstream file(filePath);
        if (!file.is_open()) {
            return false;
        }
        
        std::string xmlContent((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
        file.close();
        
        return parseProjectsXML(xmlContent, projects);
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading from XML: " << e.what() << std::endl;
        return false;
    }
}

// XML���e�̑Ó�������
bool XMLManager::validateXML(const std::string& xmlContent) {
    // ��{�I�ȑÓ����`�F�b�N
    if (xmlContent.find(XML_VERSION_HEADER) == std::string::npos) {
        return false;
    }
    if (xmlContent.find(ROOT_ELEMENT_START) == std::string::npos) {
        return false;
    }
    if (xmlContent.find(ROOT_ELEMENT_END) == std::string::npos) {
        return false;
    }
    return true;
}

// �P��v���W�F�N�g��XML�t�@�C���ɕۑ�
bool XMLManager::saveProjectToXML(const Project& project, const std::string& fileName) {
    try {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            return false;
        }
        
        file << XML_VERSION_HEADER << "\n";
        file << ROOT_ELEMENT_START << "\n";
        file << project.toXML();
        file << ROOT_ELEMENT_END << "\n";
        
        file.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving project to XML: " << e.what() << std::endl;
        return false;
    }
}

// XML�t�@�C������P��v���W�F�N�g��ǂݍ���
bool XMLManager::loadProjectFromXML(Project& project, const std::string& fileName) {
    try {
        if (!fileExists(fileName)) {
            return false;
        }
        
        std::ifstream file(fileName);
        if (!file.is_open()) {
            return false;
        }
        
        std::string xmlContent((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
        file.close();
        
        // �ȈՓI�ȃv���W�F�N�g���o
        size_t projectStart = xmlContent.find("<project");
        size_t projectEnd = xmlContent.find("</project>") + 10;
        
        if (projectStart != std::string::npos && projectEnd != std::string::npos) {
            std::string projectXML = xmlContent.substr(projectStart, projectEnd - projectStart);
            project.fromXML(projectXML);
            return true;
        }
        
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading project from XML: " << e.what() << std::endl;
        return false;
    }
}

// �o�b�N�A�b�v�t�@�C�����쐬
bool XMLManager::createBackup() {
    if (!fileExists(filePath)) {
        return false;
    }
    
    std::string backupPath = getBackupFileName();
    
    try {
        std::ifstream source(filePath, std::ios::binary);
        std::ofstream dest(backupPath, std::ios::binary);
        
        dest << source.rdbuf();
        
        source.close();
        dest.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating backup: " << e.what() << std::endl;
        return false;
    }
}

// �o�b�N�A�b�v���畜��
bool XMLManager::restoreFromBackup(const std::string& backupFileName) {
    if (!fileExists(backupFileName)) {
        return false;
    }
    
    try {
        std::ifstream source(backupFileName, std::ios::binary);
        std::ofstream dest(filePath, std::ios::binary);
        
        dest << source.rdbuf();
        
        source.close();
        dest.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error restoring from backup: " << e.what() << std::endl;
        return false;
    }
}

// �J�X�^���t�H�[�}�b�g�ŃG�N�X�|�[�g
bool XMLManager::exportToCustomFormat(const std::vector<Project>& projects, const std::string& format) {
    // ��{�I�ɂ�XML�`���ŃG�N�X�|�[�g�i�g���\�j
    return saveToXML(projects);
}

// XML���ꕶ�����G�X�P�[�v
std::string XMLManager::escapeXML(const std::string& text) {
    std::string result = text;
    size_t pos = 0;
    
    // & ���ŏ��ɏ���
    while ((pos = result.find("&", pos)) != std::string::npos) {
        result.replace(pos, 1, "&amp;");
        pos += 5;
    }
    
    pos = 0;
    while ((pos = result.find("<", pos)) != std::string::npos) {
        result.replace(pos, 1, "&lt;");
        pos += 4;
    }
    
    pos = 0;
    while ((pos = result.find(">", pos)) != std::string::npos) {
        result.replace(pos, 1, "&gt;");
        pos += 4;
    }
    
    pos = 0;
    while ((pos = result.find("\"", pos)) != std::string::npos) {
        result.replace(pos, 1, "&quot;");
        pos += 6;
    }
    
    pos = 0;
    while ((pos = result.find("'", pos)) != std::string::npos) {
        result.replace(pos, 1, "&apos;");
        pos += 6;
    }
    
    return result;
}

// XML�G�X�P�[�v�������A���G�X�P�[�v
std::string XMLManager::unescapeXML(const std::string& xmlText) {
    std::string result = xmlText;
    size_t pos = 0;
    
    while ((pos = result.find("&lt;", pos)) != std::string::npos) {
        result.replace(pos, 4, "<");
        pos += 1;
    }
    
    pos = 0;
    while ((pos = result.find("&gt;", pos)) != std::string::npos) {
        result.replace(pos, 4, ">");
        pos += 1;
    }
    
    pos = 0;
    while ((pos = result.find("&quot;", pos)) != std::string::npos) {
        result.replace(pos, 6, "\"");
        pos += 1;
    }
    
    pos = 0;
    while ((pos = result.find("&apos;", pos)) != std::string::npos) {
        result.replace(pos, 6, "'");
        pos += 1;
    }
    
    // & ���Ō�ɏ���
    pos = 0;
    while ((pos = result.find("&amp;", pos)) != std::string::npos) {
        result.replace(pos, 5, "&");
        pos += 1;
    }
    
    return result;
}

// �t�@�C�����݃`�F�b�N
bool XMLManager::fileExists(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}

// �v���W�F�N�g�Q��XML�𐶐�
std::string XMLManager::generateProjectsXML(const std::vector<Project>& projects) {
    std::ostringstream xml;
    xml << XML_VERSION_HEADER << "\n";
    xml << ROOT_ELEMENT_START << "\n";
    
    for (const auto& project : projects) {
        xml << project.toXML();
    }
    
    xml << ROOT_ELEMENT_END << "\n";
    return xml.str();
}

// XML����v���W�F�N�g�Q�����
bool XMLManager::parseProjectsXML(const std::string& xmlContent, std::vector<Project>& projects) {
    if (!validateXML(xmlContent)) {
        return false;
    }
    
    // �ȈՓI��XML�p�[�X�i���ۂ̎����ł͂�茘�S�ȃp�[�T�[���g�p�j
    projects.clear();
    
    size_t pos = 0;
    while ((pos = xmlContent.find("<project", pos)) != std::string::npos) {
        size_t endPos = xmlContent.find("</project>", pos);
        if (endPos == std::string::npos) break;
        
        endPos += 10; // "</project>" �̒���
        std::string projectXML = xmlContent.substr(pos, endPos - pos);
        
        Project project;
        project.fromXML(projectXML);
        projects.push_back(project);
        
        pos = endPos;
    }
    
    return true;
}

// ���݂̃^�C���X�^���v���擾
std::string XMLManager::getCurrentTimestamp() {
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    
    std::ostringstream oss;
    oss << (timeinfo.tm_year + 1900) << "-"
        << (timeinfo.tm_mon + 1) << "-"
        << timeinfo.tm_mday << "_"
        << timeinfo.tm_hour << "-"
        << timeinfo.tm_min << "-"
        << timeinfo.tm_sec;
    
    return oss.str();
}

// �o�b�N�A�b�v�t�@�C�����𐶐�
std::string XMLManager::getBackupFileName() {
    size_t dotPos = filePath.find_last_of('.');
    std::string baseName = (dotPos != std::string::npos) ? 
                          filePath.substr(0, dotPos) : filePath;
    std::string extension = (dotPos != std::string::npos) ? 
                           filePath.substr(dotPos) : ".xml";
    
    return baseName + "_backup_" + getCurrentTimestamp() + extension;
}