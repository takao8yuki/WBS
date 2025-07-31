#include "WBSManager.h"
#include <algorithm>
#include <sstream>

// デフォルトコンストラクタ
WBSManager::WBSManager() : nextProjectId(1), nextTaskId(1), dataFilePath("wbs_data.xml") {
}

// ファイルパス指定コンストラクタ
WBSManager::WBSManager(const std::string& dataFilePath) 
    : nextProjectId(1), nextTaskId(1), dataFilePath(dataFilePath), xmlManager(dataFilePath) {
    loadProjects(); // 初期化時にデータを読み込み
}

// プロジェクト作成
int WBSManager::createProject(const std::string& name, const std::string& description) {
    int projectId = generateNewProjectId();
    Project project(projectId, name);
    project.setDescription(description);
    projects.push_back(project);
    return projectId;
}

// プロジェクト作成（日付指定）
int WBSManager::createProject(const std::string& name, const std::string& description,
                             const Date& startDate, const Date& endDate) {
    int projectId = generateNewProjectId();
    Project project(projectId, name, description, startDate, endDate);
    projects.push_back(project);
    return projectId;
}

// プロジェクト削除
bool WBSManager::deleteProject(int projectId) {
    auto it = std::find_if(projects.begin(), projects.end(),
        [projectId](const Project& project) { return project.getProjectId() == projectId; });
    
    if (it != projects.end()) {
        projects.erase(it);
        return true;
    }
    return false;
}

// プロジェクト検索
Project* WBSManager::findProject(int projectId) {
    for (auto& project : projects) {
        if (project.getProjectId() == projectId) {
            return &project;
        }
    }
    return nullptr;
}

// タスクをプロジェクトに追加
int WBSManager::addTaskToProject(int projectId, const std::string& taskName, 
                                const std::string& description) {
    Project* project = findProject(projectId);
    if (!project) return -1;
    
    int taskId = generateNewTaskId();
    Task task(taskId, taskName, projectId);
    task.setDescription(description);
    project->addTask(task);
    return taskId;
}

// タスクをプロジェクトに追加（日付指定）
int WBSManager::addTaskToProject(int projectId, const std::string& taskName, 
                                const std::string& description, const Date& startDate, 
                                const Date& endDate) {
    Project* project = findProject(projectId);
    if (!project) return -1;
    
    int taskId = generateNewTaskId();
    Task task(taskId, taskName, description, startDate, endDate, projectId);
    project->addTask(task);
    return taskId;
}

// プロジェクトからタスクを削除
bool WBSManager::deleteTaskFromProject(int projectId, int taskId) {
    Project* project = findProject(projectId);
    if (!project) return false;
    
    return project->removeTask(taskId);
}

// サブタスクを追加
bool WBSManager::addSubTask(int projectId, int parentTaskId, const std::string& taskName,
                           const std::string& description) {
    Project* project = findProject(projectId);
    if (!project) return false;
    
    Task* parentTask = project->findTask(parentTaskId);
    if (!parentTask) return false;
    
    int taskId = generateNewTaskId();
    Task subTask(taskId, taskName, projectId);
    subTask.setDescription(description);
    subTask.setParentTaskId(parentTaskId);
    parentTask->addSubTask(subTask);
    return true;
}

// プロジェクトデータを読み込み
bool WBSManager::loadProjects() {
    bool result = xmlManager.loadFromXML(projects);
    if (result) {
        updateMaxIds();
    }
    return result;
}

// プロジェクトデータを保存
bool WBSManager::saveProjects() {
    return xmlManager.saveToXML(projects);
}

// XMLにエクスポート
bool WBSManager::exportToXML(const std::string& exportPath) {
    XMLManager exportManager(exportPath);
    return exportManager.saveToXML(projects);
}

// XMLからインポート
bool WBSManager::importFromXML(const std::string& importPath) {
    XMLManager importManager(importPath);
    std::vector<Project> importedProjects;
    bool result = importManager.loadFromXML(importedProjects);
    if (result) {
        projects.insert(projects.end(), importedProjects.begin(), importedProjects.end());
        updateMaxIds();
    }
    return result;
}

// 完了プロジェクト数を取得
int WBSManager::getCompletedProjectCount() const {
    int count = 0;
    for (const auto& project : projects) {
        if (project.isCompleted()) {
            count++;
        }
    }
    return count;
}

// 総タスク数を取得
int WBSManager::getTotalTaskCount() const {
    int count = 0;
    for (const auto& project : projects) {
        count += project.getTotalTaskCount();
    }
    return count;
}

// 完了タスク数を取得
int WBSManager::getCompletedTaskCount() const {
    int count = 0;
    for (const auto& project : projects) {
        count += project.getCompletedTaskCount();
    }
    return count;
}

// 名前でプロジェクトを検索
std::vector<Project*> WBSManager::findProjectsByName(const std::string& name) {
    std::vector<Project*> result;
    for (auto& project : projects) {
        if (project.getName().find(name) != std::string::npos) {
            result.push_back(&project);
        }
    }
    return result;
}

// 名前でタスクを検索
std::vector<Task*> WBSManager::findTasksByName(const std::string& name) {
    std::vector<Task*> result;
    for (auto& project : projects) {
        for (auto& task : project.getTasks()) {
            if (task.getName().find(name) != std::string::npos) {
                result.push_back(const_cast<Task*>(&task));
            }
        }
    }
    return result;
}

// 担当者でタスクを検索
std::vector<Task*> WBSManager::findTasksByAssignee(const std::string& assignee) {
    std::vector<Task*> result;
    for (auto& project : projects) {
        for (auto& task : project.getTasks()) {
            if (task.getAssignedTo() == assignee) {
                result.push_back(const_cast<Task*>(&task));
            }
        }
    }
    return result;
}

// 状態でタスクを検索
std::vector<Task*> WBSManager::findTasksByStatus(TaskStatus status) {
    std::vector<Task*> result;
    for (auto& project : projects) {
        for (auto& task : project.getTasks()) {
            if (task.getStatus() == status) {
                result.push_back(const_cast<Task*>(&task));
            }
        }
    }
    return result;
}

// 優先度でタスクを検索
std::vector<Task*> WBSManager::findTasksByPriority(Priority priority) {
    std::vector<Task*> result;
    for (auto& project : projects) {
        for (auto& task : project.getTasks()) {
            if (task.getPriority() == priority) {
                result.push_back(const_cast<Task*>(&task));
            }
        }
    }
    return result;
}

// プロジェクトレポートを生成
std::string WBSManager::generateProjectReport(int projectId) {
    Project* project = findProject(projectId);
    if (!project) return "";
    
    std::ostringstream report;
    report << "=== Project Report ===\n";
    report << "Project ID: " << project->getProjectId() << "\n";
    report << "Name: " << project->getName() << "\n";
    report << "Description: " << project->getDescription() << "\n";
    report << "Status: " << projectStatusToString(project->getStatus()) << "\n";
    report << "Start Date: " << project->getStartDate().toString() << "\n";
    report << "End Date: " << project->getEndDate().toString() << "\n";
    report << "Completion: " << project->getCompletionPercentage() << "%\n";
    report << "Tasks: " << project->getTaskCount() << "\n";
    
    const auto& tasks = project->getTasks();
    for (const auto& task : tasks) {
        report << "  - " << task.getName() << " (" << taskStatusToString(task.getStatus()) << ")\n";
    }
    
    return report.str();
}

// タスクレポートを生成
std::string WBSManager::generateTaskReport(int projectId, int taskId) {
    Project* project = findProject(projectId);
    if (!project) return "";
    
    Task* task = project->findTask(taskId);
    if (!task) return "";
    
    std::ostringstream report;
    report << "=== Task Report ===\n";
    report << "Task ID: " << task->getTaskId() << "\n";
    report << "Name: " << task->getName() << "\n";
    report << "Description: " << task->getDescription() << "\n";
    report << "Status: " << taskStatusToString(task->getStatus()) << "\n";
    report << "Priority: " << priorityToString(task->getPriority()) << "\n";
    report << "Assigned To: " << task->getAssignedTo() << "\n";
    report << "Start Date: " << task->getStartDate().toString() << "\n";
    report << "End Date: " << task->getEndDate().toString() << "\n";
    report << "Duration: " << task->getDuration() << " days\n";
    
    return report.str();
}

// サマリーレポートを生成
std::string WBSManager::generateSummaryReport() {
    std::ostringstream report;
    report << "=== Summary Report ===\n";
    report << "Total Projects: " << getTotalProjectCount() << "\n";
    report << "Completed Projects: " << getCompletedProjectCount() << "\n";
    report << "Total Tasks: " << getTotalTaskCount() << "\n";
    report << "Completed Tasks: " << getCompletedTaskCount() << "\n";
    
    if (getTotalTaskCount() > 0) {
        double completionRate = (static_cast<double>(getCompletedTaskCount()) / getTotalTaskCount()) * 100.0;
        report << "Overall Completion Rate: " << completionRate << "%\n";
    }
    
    return report.str();
}

// 全プロジェクトの状態を更新
void WBSManager::updateAllProjectStatuses() {
    for (auto& project : projects) {
        project.updateProjectStatus();
    }
}

// プロジェクト名の一意性チェック
bool WBSManager::isProjectNameUnique(const std::string& name, int excludeProjectId) {
    for (const auto& project : projects) {
        if (project.getName() == name && project.getProjectId() != excludeProjectId) {
            return false;
        }
    }
    return true;
}

// IDを初期化
void WBSManager::initializeIds() {
    nextProjectId = 1;
    nextTaskId = 1;
    updateMaxIds();
}

// プロジェクト内のタスクを検索
Task* WBSManager::findTaskInProject(Project& project, int taskId) {
    return project.findTask(taskId);
}

// 最大IDを更新
void WBSManager::updateMaxIds() {
    int maxProjectId = 0;
    int maxTaskId = 0;
    
    for (const auto& project : projects) {
        if (project.getProjectId() > maxProjectId) {
            maxProjectId = project.getProjectId();
        }
        
        for (const auto& task : project.getTasks()) {
            if (task.getTaskId() > maxTaskId) {
                maxTaskId = task.getTaskId();
            }
        }
    }
    
    nextProjectId = maxProjectId + 1;
    nextTaskId = maxTaskId + 1;
}