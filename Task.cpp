#include "Task.h"
#include <algorithm>
#include <sstream>

// デフォルトコンストラクタ
Task::Task() : taskId(-1), duration(0), parentTaskId(-1), projectId(-1), 
               status(TaskStatus::NotStarted), priority(Priority::Medium) {
}

// 基本コンストラクタ
Task::Task(int taskId, const std::string& name, int projectId) 
    : taskId(taskId), name(name), projectId(projectId), duration(0), 
      parentTaskId(-1), status(TaskStatus::NotStarted), priority(Priority::Medium) {
}

// 詳細コンストラクタ
Task::Task(int taskId, const std::string& name, const std::string& description,
           const Date& startDate, const Date& endDate, int projectId)
    : taskId(taskId), name(name), description(description), startDate(startDate),
      endDate(endDate), projectId(projectId), parentTaskId(-1),
      status(TaskStatus::NotStarted), priority(Priority::Medium) {
    calculateDuration();
}

// サブタスクを追加
void Task::addSubTask(const Task& task) {
    subTasks.push_back(task);
    // 親タスクのIDを設定
    subTasks.back().setParentTaskId(this->taskId);
}

// サブタスクを削除
bool Task::removeSubTask(int taskId) {
    auto it = std::find_if(subTasks.begin(), subTasks.end(),
        [taskId](const Task& task) { return task.getTaskId() == taskId; });
    
    if (it != subTasks.end()) {
        subTasks.erase(it);
        return true;
    }
    
    // サブタスクの中を再帰的に検索
    for (auto& subTask : subTasks) {
        if (subTask.removeSubTask(taskId)) {
            return true;
        }
    }
    
    return false;
}

// サブタスクを検索
Task* Task::findSubTask(int taskId) {
    for (auto& subTask : subTasks) {
        if (subTask.getTaskId() == taskId) {
            return &subTask;
        }
        
        // 再帰的に検索
        Task* found = subTask.findSubTask(taskId);
        if (found) {
            return found;
        }
    }
    return nullptr;
}

// タスクを更新
void Task::updateTask(const std::string& name, const std::string& description,
                     const Date& startDate, const Date& endDate) {
    this->name = name;
    this->description = description;
    this->startDate = startDate;
    this->endDate = endDate;
    calculateDuration();
}

// 期間を計算
void Task::calculateDuration() {
    if (startDate.isValid() && endDate.isValid()) {
        // 簡単な日数計算（実際の実装ではより正確な計算が必要）
        int startDays = startDate.getYear() * 365 + startDate.getMonth() * 30 + startDate.getDay();
        int endDays = endDate.getYear() * 365 + endDate.getMonth() * 30 + endDate.getDay();
        duration = endDays - startDays;
        if (duration < 0) duration = 0;
    }
}

// XMLに変換
std::string Task::toXML() const {
    std::ostringstream xml;
    xml << "<task id=\"" << taskId << "\">\n";
    xml << "  <name>" << name << "</name>\n";
    xml << "  <description>" << description << "</description>\n";
    xml << "  <start_date>" << startDate.toString() << "</start_date>\n";
    xml << "  <end_date>" << endDate.toString() << "</end_date>\n";
    xml << "  <duration>" << duration << "</duration>\n";
    xml << "  <parent_task_id>" << parentTaskId << "</parent_task_id>\n";
    xml << "  <project_id>" << projectId << "</project_id>\n";
    xml << "  <status>" << taskStatusToString(status) << "</status>\n";
    xml << "  <priority>" << priorityToString(priority) << "</priority>\n";
    xml << "  <assigned_to>" << assignedTo << "</assigned_to>\n";
    
    if (!subTasks.empty()) {
        xml << "  <subtasks>\n";
        for (const auto& subTask : subTasks) {
            std::string subTaskXML = subTask.toXML();
            // インデントを追加
            size_t pos = 0;
            while ((pos = subTaskXML.find('\n', pos)) != std::string::npos) {
                subTaskXML.insert(pos + 1, "  ");
                pos += 3;
            }
            xml << "  " << subTaskXML;
        }
        xml << "  </subtasks>\n";
    }
    
    xml << "</task>\n";
    return xml.str();
}

// XMLから読み込み（簡易実装）
void Task::fromXML(const std::string& xmlData) {
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