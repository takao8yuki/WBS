#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Project.h"
#include "Task.h"
#include "XMLManager.h"

class WBSManager {
private:
    std::vector<Project> projects;
    XMLManager xmlManager;
    int nextProjectId;
    int nextTaskId;
    std::string dataFilePath;

public:
    // �R���X�g���N�^
    WBSManager();
    WBSManager(const std::string& dataFilePath);
    
    // �v���W�F�N�g�Ǘ�
    int createProject(const std::string& name, const std::string& description = "");
    int createProject(const std::string& name, const std::string& description,
                     const Date& startDate, const Date& endDate);
    bool deleteProject(int projectId);
    Project* findProject(int projectId);
    const std::vector<Project>& getProjects() const { return projects; }
    
    // �^�X�N�Ǘ�
    int addTaskToProject(int projectId, const std::string& taskName, 
                        const std::string& description = "");
    int addTaskToProject(int projectId, const std::string& taskName, 
                        const std::string& description, const Date& startDate, 
                        const Date& endDate);
    bool deleteTaskFromProject(int projectId, int taskId);
    bool addSubTask(int projectId, int parentTaskId, const std::string& taskName,
                   const std::string& description = "");
    
    // �f�[�^�i����
    bool loadProjects();
    bool saveProjects();
    bool exportToXML(const std::string& exportPath);
    bool importFromXML(const std::string& importPath);
    
    // �v���W�F�N�g���v
    int getTotalProjectCount() const { return static_cast<int>(projects.size()); }
    int getCompletedProjectCount() const;
    int getTotalTaskCount() const;
    int getCompletedTaskCount() const;
    
    // �����@�\
    std::vector<Project*> findProjectsByName(const std::string& name);
    std::vector<Task*> findTasksByName(const std::string& name);
    std::vector<Task*> findTasksByAssignee(const std::string& assignee);
    std::vector<Task*> findTasksByStatus(TaskStatus status);
    std::vector<Task*> findTasksByPriority(Priority priority);
    
    // ���|�[�g����
    std::string generateProjectReport(int projectId);
    std::string generateTaskReport(int projectId, int taskId);
    std::string generateSummaryReport();
    
    // ���[�e�B���e�B
    void updateAllProjectStatuses();
    bool isProjectNameUnique(const std::string& name, int excludeProjectId = -1);
    
    // �t�@�C���Ǘ�
    void setDataFilePath(const std::string& path) { dataFilePath = path; xmlManager.setFilePath(path); }
    const std::string& getDataFilePath() const { return dataFilePath; }

private:
    // �v���C�x�[�g�w���p�[���\�b�h
    int generateNewProjectId() { return ++nextProjectId; }
    int generateNewTaskId() { return ++nextTaskId; }
    void initializeIds();
    Task* findTaskInProject(Project& project, int taskId);
    void updateMaxIds();
};