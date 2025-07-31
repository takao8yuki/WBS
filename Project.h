#pragma once
#include <string>
#include <vector>
#include "Date.h"
#include "Enums.h"
#include "Task.h"

class Project {
private:
    int projectId;
    std::string name;
    std::string description;
    Date startDate;
    Date endDate;
    ProjectStatus status;
    std::vector<Task> tasks;

public:
    // �R���X�g���N�^
    Project();
    Project(int projectId, const std::string& name);
    Project(int projectId, const std::string& name, const std::string& description,
            const Date& startDate, const Date& endDate);
    
    // �Q�b�^�[
    int getProjectId() const { return projectId; }
    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }
    const Date& getStartDate() const { return startDate; }
    const Date& getEndDate() const { return endDate; }
    ProjectStatus getStatus() const { return status; }
    const std::vector<Task>& getTasks() const { return tasks; }
    
    // �Z�b�^�[
    void setProjectId(int id) { projectId = id; }
    void setName(const std::string& name) { this->name = name; }
    void setDescription(const std::string& description) { this->description = description; }
    void setStartDate(const Date& date) { startDate = date; }
    void setEndDate(const Date& date) { endDate = date; }
    void setStatus(ProjectStatus status) { this->status = status; }
    
    // �^�X�N�Ǘ����\�b�h
    void addTask(const Task& task);
    bool removeTask(int taskId);
    Task* findTask(int taskId);
    void updateProject(const std::string& name, const std::string& description,
                      const Date& startDate, const Date& endDate);
    
    // ���[�e�B���e�B���\�b�h
    int getTaskCount() const { return static_cast<int>(tasks.size()); }
    int getCompletedTaskCount() const;
    double getCompletionPercentage() const;
    void updateProjectStatus();
    bool isCompleted() const { return status == ProjectStatus::Completed; }
    
    // ���v���
    int getTotalTaskCount() const; // �T�u�^�X�N���܂ޑ��^�X�N��
    Date getEarliestStartDate() const;
    Date getLatestEndDate() const;
    
    // XML�֘A���\�b�h
    std::string toXML() const;
    void fromXML(const std::string& xmlData);
};