#pragma once
#include <string>
#include <vector>
#include "Date.h"
#include "Enums.h"

class Task {
private:
    int taskId;
    std::string name;
    std::string description;
    Date startDate;
    Date endDate;
    int duration;           // 日数
    int parentTaskId;       // 親タスクのID（-1の場合は親なし）
    int projectId;          // 所属するプロジェクトのID
    TaskStatus status;
    Priority priority;
    std::string assignedTo; // 担当者
    std::vector<Task> subTasks; // サブタスク

public:
    // コンストラクタ
    Task();
    Task(int taskId, const std::string& name, int projectId);
    Task(int taskId, const std::string& name, const std::string& description, 
         const Date& startDate, const Date& endDate, int projectId);
    
    // ゲッター
    int getTaskId() const { return taskId; }
    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
    const Date& getStartDate() const { return startDate; }
    const Date& getEndDate() const { return endDate; }
    int getDuration() const { return duration; }
    int getParentTaskId() const { return parentTaskId; }
    int getProjectId() const { return projectId; }
    TaskStatus getStatus() const { return status; }
    Priority getPriority() const { return priority; }
    const std::string& getAssignedTo() const { return assignedTo; }
    const std::vector<Task>& getSubTasks() const { return subTasks; }
    
    // セッター
    void setTaskId(int id) { taskId = id; }
    void setName(const std::string& name) { this->name = name; }
    void setDescription(const std::string& description) { this->description = description; }
    void setStartDate(const Date& date) { startDate = date; calculateDuration(); }
    void setEndDate(const Date& date) { endDate = date; calculateDuration(); }
    void setParentTaskId(int id) { parentTaskId = id; }
    void setProjectId(int id) { projectId = id; }
    void setStatus(TaskStatus status) { this->status = status; }
    void setPriority(Priority priority) { this->priority = priority; }
    void setAssignedTo(const std::string& assignedTo) { this->assignedTo = assignedTo; }
    
    // タスク管理メソッド
    void addSubTask(const Task& task);
    bool removeSubTask(int taskId);
    Task* findSubTask(int taskId);
    void updateTask(const std::string& name, const std::string& description,
                   const Date& startDate, const Date& endDate);
    
    // ユーティリティメソッド
    void calculateDuration();
    bool hasSubTasks() const { return !subTasks.empty(); }
    int getSubTaskCount() const { return static_cast<int>(subTasks.size()); }
    bool isCompleted() const { return status == TaskStatus::Completed; }
    
    // XML関連メソッド
    std::string toXML() const;
    void fromXML(const std::string& xmlData);
};