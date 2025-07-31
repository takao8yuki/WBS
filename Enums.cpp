#include "Enums.h"

// ProjectStatus�𕶎���ɕϊ�
std::string projectStatusToString(ProjectStatus status) {
    switch (status) {
        case ProjectStatus::Planning:
            return "Planning";
        case ProjectStatus::InProgress:
            return "InProgress";
        case ProjectStatus::Completed:
            return "Completed";
        case ProjectStatus::OnHold:
            return "OnHold";
        default:
            return "Unknown";
    }
}

// TaskStatus�𕶎���ɕϊ�
std::string taskStatusToString(TaskStatus status) {
    switch (status) {
        case TaskStatus::NotStarted:
            return "NotStarted";
        case TaskStatus::InProgress:
            return "InProgress";
        case TaskStatus::Completed:
            return "Completed";
        case TaskStatus::Blocked:
            return "Blocked";
        default:
            return "Unknown";
    }
}

// Priority�𕶎���ɕϊ�
std::string priorityToString(Priority priority) {
    switch (priority) {
        case Priority::Low:
            return "Low";
        case Priority::Medium:
            return "Medium";
        case Priority::High:
            return "High";
        case Priority::Critical:
            return "Critical";
        default:
            return "Unknown";
    }
}

// �����񂩂�ProjectStatus�ɕϊ�
ProjectStatus stringToProjectStatus(const std::string& str) {
    if (str == "Planning") return ProjectStatus::Planning;
    if (str == "InProgress") return ProjectStatus::InProgress;
    if (str == "Completed") return ProjectStatus::Completed;
    if (str == "OnHold") return ProjectStatus::OnHold;
    return ProjectStatus::Planning; // �f�t�H���g
}

// �����񂩂�TaskStatus�ɕϊ�
TaskStatus stringToTaskStatus(const std::string& str) {
    if (str == "NotStarted") return TaskStatus::NotStarted;
    if (str == "InProgress") return TaskStatus::InProgress;
    if (str == "Completed") return TaskStatus::Completed;
    if (str == "Blocked") return TaskStatus::Blocked;
    return TaskStatus::NotStarted; // �f�t�H���g
}

// �����񂩂�Priority�ɕϊ�
Priority stringToPriority(const std::string& str) {
    if (str == "Low") return Priority::Low;
    if (str == "Medium") return Priority::Medium;
    if (str == "High") return Priority::High;
    if (str == "Critical") return Priority::Critical;
    return Priority::Medium; // �f�t�H���g
}