#include "Project.h"
#include <algorithm>
#include <sstream>

// デフォルトコンストラクタ
Project::Project() : projectId(-1), status(ProjectStatus::Planning) {
}

// 基本コンストラクタ
Project::Project(int projectId, const std::string& name) 
    : projectId(projectId), name(name), status(ProjectStatus::Planning) {
}

// 詳細コンストラクタ
Project::Project(int projectId, const std::string& name, const std::string& description,
                const Date& startDate, const Date& endDate)
    : projectId(projectId), name(name), description(description), 
      startDate(startDate), endDate(endDate), status(ProjectStatus::Planning) {
}

// タスクを追加
void Project::addTask(const Task& task) {
    tasks.push_back(task);
}

// タスクを削除
bool Project::removeTask(int taskId) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [taskId](const Task& task) { return task.getTaskId() == taskId; });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    return false;
}

// タスクを検索
Task* Project::findTask(int taskId) {
    for (auto& task : tasks) {
        if (task.getTaskId() == taskId) {
            return &task;
        }
        
        // サブタスクも検索
        Task* found = task.findSubTask(taskId);
        if (found) {
            return found;
        }
    }
    return nullptr;
}

// プロジェクトを更新
void Project::updateProject(const std::string& name, const std::string& description,
                           const Date& startDate, const Date& endDate) {
    this->name = name;
    this->description = description;
    this->startDate = startDate;
    this->endDate = endDate;
}

// 完了タスク数を取得
int Project::getCompletedTaskCount() const {
    int count = 0;
    for (const auto& task : tasks) {
        if (task.isCompleted()) {
            count++;
        }
    }
    return count;
}

// 完了率を計算
double Project::getCompletionPercentage() const {
    if (tasks.empty()) return 0.0;
    return (static_cast<double>(getCompletedTaskCount()) / tasks.size()) * 100.0;
}

// プロジェクト状態を更新
void Project::updateProjectStatus() {
    if (tasks.empty()) {
        status = ProjectStatus::Planning;
        return;
    }
    
    int completedTasks = getCompletedTaskCount();
    if (completedTasks == static_cast<int>(tasks.size())) {
        status = ProjectStatus::Completed;
    } else if (completedTasks > 0) {
        status = ProjectStatus::InProgress;
    } else {
        status = ProjectStatus::Planning;
    }
}

// 総タスク数（サブタスクも含む）
int Project::getTotalTaskCount() const {
    int count = static_cast<int>(tasks.size());
    for (const auto& task : tasks) {
        count += task.getSubTaskCount();
    }
    return count;
}

// 最早開始日を取得
Date Project::getEarliestStartDate() const {
    if (tasks.empty()) return startDate;
    
    Date earliest = tasks[0].getStartDate();
    for (const auto& task : tasks) {
        if (task.getStartDate() < earliest) {
            earliest = task.getStartDate();
        }
    }
    return earliest;
}

// 最遅終了日を取得
Date Project::getLatestEndDate() const {
    if (tasks.empty()) return endDate;
    
    Date latest = tasks[0].getEndDate();
    for (const auto& task : tasks) {
        if (task.getEndDate() > latest) {
            latest = task.getEndDate();
        }
    }
    return latest;
}

// XMLに変換
std::string Project::toXML() const {
    std::ostringstream xml;
    xml << "<project id=\"" << projectId << "\">\n";
    xml << "  <name>" << name << "</name>\n";
    xml << "  <description>" << description << "</description>\n";
    xml << "  <start_date>" << startDate.toString() << "</start_date>\n";
    xml << "  <end_date>" << endDate.toString() << "</end_date>\n";
    xml << "  <status>" << projectStatusToString(status) << "</status>\n";
    
    if (!tasks.empty()) {
        xml << "  <tasks>\n";
        for (const auto& task : tasks) {
            std::string taskXML = task.toXML();
            // インデントを追加
            size_t pos = 0;
            while ((pos = taskXML.find('\n', pos)) != std::string::npos) {
                taskXML.insert(pos + 1, "  ");
                pos += 3;
            }
            xml << "  " << taskXML;
        }
        xml << "  </tasks>\n";
    }
    
    xml << "</project>\n";
    return xml.str();
}

// XMLから読み込み（簡易実装）
void Project::fromXML(const std::string& xmlData) {
    // 実際の実装では適切なXMLパーサーを使用
    // ここでは簡易的な実装
    
    // XMLデータから値を抽出する処理
    // この実装は後で適切なXMLパーサーで置き換える必要がある
    size_t pos;
    
    // name の抽出
    pos = xmlData.find("<name>");
    if (pos != std::string::npos) {
        size_t endPos = xmlData.find("</name>", pos);
        if (endPos != std::string::npos) {
            name = xmlData.substr(pos + 6, endPos - pos - 6);
        }
    }
    
    // 他のフィールドも同様に抽出...
    // 実際の実装ではより堅牢なXMLパーシングが必要
}