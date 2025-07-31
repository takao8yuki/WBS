#include "Project.h"
#include <algorithm>
#include <sstream>

// �f�t�H���g�R���X�g���N�^
Project::Project() : projectId(-1), status(ProjectStatus::Planning) {
}

// ��{�R���X�g���N�^
Project::Project(int projectId, const std::string& name) 
    : projectId(projectId), name(name), status(ProjectStatus::Planning) {
}

// �ڍ׃R���X�g���N�^
Project::Project(int projectId, const std::string& name, const std::string& description,
                const Date& startDate, const Date& endDate)
    : projectId(projectId), name(name), description(description), 
      startDate(startDate), endDate(endDate), status(ProjectStatus::Planning) {
}

// �^�X�N��ǉ�
void Project::addTask(const Task& task) {
    tasks.push_back(task);
}

// �^�X�N���폜
bool Project::removeTask(int taskId) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
        [taskId](const Task& task) { return task.getTaskId() == taskId; });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        return true;
    }
    return false;
}

// �^�X�N������
Task* Project::findTask(int taskId) {
    for (auto& task : tasks) {
        if (task.getTaskId() == taskId) {
            return &task;
        }
        
        // �T�u�^�X�N������
        Task* found = task.findSubTask(taskId);
        if (found) {
            return found;
        }
    }
    return nullptr;
}

// �v���W�F�N�g���X�V
void Project::updateProject(const std::string& name, const std::string& description,
                           const Date& startDate, const Date& endDate) {
    this->name = name;
    this->description = description;
    this->startDate = startDate;
    this->endDate = endDate;
}

// �����^�X�N�����擾
int Project::getCompletedTaskCount() const {
    int count = 0;
    for (const auto& task : tasks) {
        if (task.isCompleted()) {
            count++;
        }
    }
    return count;
}

// ���������v�Z
double Project::getCompletionPercentage() const {
    if (tasks.empty()) return 0.0;
    return (static_cast<double>(getCompletedTaskCount()) / tasks.size()) * 100.0;
}

// �v���W�F�N�g��Ԃ��X�V
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

// ���^�X�N���i�T�u�^�X�N���܂ށj
int Project::getTotalTaskCount() const {
    int count = static_cast<int>(tasks.size());
    for (const auto& task : tasks) {
        count += task.getSubTaskCount();
    }
    return count;
}

// �ő��J�n�����擾
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

// �Œx�I�������擾
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

// XML�ɕϊ�
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
            // �C���f���g��ǉ�
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

// XML����ǂݍ��݁i�ȈՎ����j
void Project::fromXML(const std::string& xmlData) {
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