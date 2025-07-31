#include "Task.h"
#include <algorithm>
#include <sstream>

// �f�t�H���g�R���X�g���N�^
Task::Task() : taskId(-1), duration(0), parentTaskId(-1), projectId(-1), 
               status(TaskStatus::NotStarted), priority(Priority::Medium) {
}

// ��{�R���X�g���N�^
Task::Task(int taskId, const std::string& name, int projectId) 
    : taskId(taskId), name(name), projectId(projectId), duration(0), 
      parentTaskId(-1), status(TaskStatus::NotStarted), priority(Priority::Medium) {
}

// �ڍ׃R���X�g���N�^
Task::Task(int taskId, const std::string& name, const std::string& description,
           const Date& startDate, const Date& endDate, int projectId)
    : taskId(taskId), name(name), description(description), startDate(startDate),
      endDate(endDate), projectId(projectId), parentTaskId(-1),
      status(TaskStatus::NotStarted), priority(Priority::Medium) {
    calculateDuration();
}

// �T�u�^�X�N��ǉ�
void Task::addSubTask(const Task& task) {
    subTasks.push_back(task);
    // �e�^�X�N��ID��ݒ�
    subTasks.back().setParentTaskId(this->taskId);
}

// �T�u�^�X�N���폜
bool Task::removeSubTask(int taskId) {
    auto it = std::find_if(subTasks.begin(), subTasks.end(),
        [taskId](const Task& task) { return task.getTaskId() == taskId; });
    
    if (it != subTasks.end()) {
        subTasks.erase(it);
        return true;
    }
    
    // �T�u�^�X�N�̒����ċA�I�Ɍ���
    for (auto& subTask : subTasks) {
        if (subTask.removeSubTask(taskId)) {
            return true;
        }
    }
    
    return false;
}

// �T�u�^�X�N������
Task* Task::findSubTask(int taskId) {
    for (auto& subTask : subTasks) {
        if (subTask.getTaskId() == taskId) {
            return &subTask;
        }
        
        // �ċA�I�Ɍ���
        Task* found = subTask.findSubTask(taskId);
        if (found) {
            return found;
        }
    }
    return nullptr;
}

// �^�X�N���X�V
void Task::updateTask(const std::string& name, const std::string& description,
                     const Date& startDate, const Date& endDate) {
    this->name = name;
    this->description = description;
    this->startDate = startDate;
    this->endDate = endDate;
    calculateDuration();
}

// ���Ԃ��v�Z
void Task::calculateDuration() {
    if (startDate.isValid() && endDate.isValid()) {
        // �ȒP�ȓ����v�Z�i���ۂ̎����ł͂�萳�m�Ȍv�Z���K�v�j
        int startDays = startDate.getYear() * 365 + startDate.getMonth() * 30 + startDate.getDay();
        int endDays = endDate.getYear() * 365 + endDate.getMonth() * 30 + endDate.getDay();
        duration = endDays - startDays;
        if (duration < 0) duration = 0;
    }
}

// XML�ɕϊ�
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
            // �C���f���g��ǉ�
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

// XML����ǂݍ��݁i�ȈՎ����j
void Task::fromXML(const std::string& xmlData) {
    // ���ۂ̎����ł͓K�؂�XML�p�[�T�[���g�p
    // �����ł͊ȈՓI�Ȏ���
    
    // XML�f�[�^����l�𒊏o���鏈��
    // ���̎����͌�œK�؂�XML�p�[�T�[�Œu��������K�v������
    size_t pos;
    
    // name �̒��o
    pos = xmlData.find("<name>");
    if (pos != std::string::npos) {
        size_t endPos = xmlData.find("</name>", pos);
        if (endPos != std::string::npos) {
            name = xmlData.substr(pos + 6, endPos - pos - 6);
        }
    }
    
    // ���̃t�B�[���h�����l�ɒ��o...
    // ���ۂ̎����ł͂�茘�S��XML�p�[�V���O���K�v
}