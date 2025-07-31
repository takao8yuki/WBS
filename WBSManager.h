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
    // コンストラクタ
    WBSManager();
    WBSManager(const std::string& dataFilePath);
    
    // プロジェクト管理
    int createProject(const std::string& name, const std::string& description = "");
    int createProject(const std::string& name, const std::string& description,
                     const Date& startDate, const Date& endDate);
    bool deleteProject(int projectId);
    Project* findProject(int projectId);
    const std::vector<Project>& getProjects() const { return projects; }
    
    // タスク管理
    int addTaskToProject(int projectId, const std::string& taskName, 
                        const std::string& description = "");
    int addTaskToProject(int projectId, const std::string& taskName, 
                        const std::string& description, const Date& startDate, 
                        const Date& endDate);
    bool deleteTaskFromProject(int projectId, int taskId);
    bool addSubTask(int projectId, int parentTaskId, const std::string& taskName,
                   const std::string& description = "");
    
    // データ永続化
    bool loadProjects();
    bool saveProjects();
    bool exportToXML(const std::string& exportPath);
    bool importFromXML(const std::string& importPath);
    
    // プロジェクト統計
    int getTotalProjectCount() const { return static_cast<int>(projects.size()); }
    int getCompletedProjectCount() const;
    int getTotalTaskCount() const;
    int getCompletedTaskCount() const;
    
    // 検索機能
    std::vector<Project*> findProjectsByName(const std::string& name);
    std::vector<Task*> findTasksByName(const std::string& name);
    std::vector<Task*> findTasksByAssignee(const std::string& assignee);
    std::vector<Task*> findTasksByStatus(TaskStatus status);
    std::vector<Task*> findTasksByPriority(Priority priority);
    
    // レポート生成
    std::string generateProjectReport(int projectId);
    std::string generateTaskReport(int projectId, int taskId);
    std::string generateSummaryReport();
    
    // ユーティリティ
    void updateAllProjectStatuses();
    bool isProjectNameUnique(const std::string& name, int excludeProjectId = -1);
    
    // ファイル管理
    void setDataFilePath(const std::string& path) { dataFilePath = path; xmlManager.setFilePath(path); }
    const std::string& getDataFilePath() const { return dataFilePath; }

private:
    // プライベートヘルパーメソッド
    int generateNewProjectId() { return ++nextProjectId; }
    int generateNewTaskId() { return ++nextTaskId; }
    void initializeIds();
    Task* findTaskInProject(Project& project, int taskId);
    void updateMaxIds();
};