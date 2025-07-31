#include "Enums.h"

// ProjectStatusを文字列に変換
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

// TaskStatusを文字列に変換
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

// Priorityを文字列に変換
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

// 文字列からProjectStatusに変換
ProjectStatus stringToProjectStatus(const std::string& str) {
    if (str == "Planning") return ProjectStatus::Planning;
    if (str == "InProgress") return ProjectStatus::InProgress;
    if (str == "Completed") return ProjectStatus::Completed;
    if (str == "OnHold") return ProjectStatus::OnHold;
    return ProjectStatus::Planning; // デフォルト
}

// 文字列からTaskStatusに変換
TaskStatus stringToTaskStatus(const std::string& str) {
    if (str == "NotStarted") return TaskStatus::NotStarted;
    if (str == "InProgress") return TaskStatus::InProgress;
    if (str == "Completed") return TaskStatus::Completed;
    if (str == "Blocked") return TaskStatus::Blocked;
    return TaskStatus::NotStarted; // デフォルト
}

// 文字列からPriorityに変換
Priority stringToPriority(const std::string& str) {
    if (str == "Low") return Priority::Low;
    if (str == "Medium") return Priority::Medium;
    if (str == "High") return Priority::High;
    if (str == "Critical") return Priority::Critical;
    return Priority::Medium; // デフォルト
}