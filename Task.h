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
    int duration;           // ����
    int parentTaskId;       // �e�^�X�N��ID�i-1�̏ꍇ�͐e�Ȃ��j
    int projectId;          // ��������v���W�F�N�g��ID
    TaskStatus status;
    Priority priority;
    std::string assignedTo; // �S����
    std::vector<Task> subTasks; // �T�u�^�X�N

public:
    // �R���X�g���N�^
    Task();
    Task(int taskId, const std::string& name, int projectId);
    Task(int taskId, const std::string& name, const std::string& description, 
         const Date& startDate, const Date& endDate, int projectId);
    
    // �Q�b�^�[
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
    
    // �Z�b�^�[
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
    
    // �^�X�N�Ǘ����\�b�h
    void addSubTask(const Task& task);
    bool removeSubTask(int taskId);
    Task* findSubTask(int taskId);
    void updateTask(const std::string& name, const std::string& description,
                   const Date& startDate, const Date& endDate);
    
    // ���[�e�B���e�B���\�b�h
    void calculateDuration();
    bool hasSubTasks() const { return !subTasks.empty(); }
    int getSubTaskCount() const { return static_cast<int>(subTasks.size()); }
    bool isCompleted() const { return status == TaskStatus::Completed; }
    
    // XML�֘A���\�b�h
    std::string toXML() const;
    void fromXML(const std::string& xmlData);
};