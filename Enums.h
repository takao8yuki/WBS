#pragma once
#include <string>

// プロジェクトの状態を表す列挙型
enum class ProjectStatus {
    Planning,       // 計画中
    InProgress,     // 進行中
    Completed,      // 完了
    OnHold          // 保留中
};

// タスクの状態を表す列挙型
enum class TaskStatus {
    NotStarted,     // 未開始
    InProgress,     // 進行中
    Completed,      // 完了
    Blocked         // ブロック中
};

// 優先度を表す列挙型
enum class Priority {
    Low,            // 低
    Medium,         // 中
    High,           // 高
    Critical        // 緊急
};

// 列挙型を文字列に変換するユーティリティ関数
std::string projectStatusToString(ProjectStatus status);
std::string taskStatusToString(TaskStatus status);
std::string priorityToString(Priority priority);

// 文字列から列挙型に変換するユーティリティ関数
ProjectStatus stringToProjectStatus(const std::string& str);
TaskStatus stringToTaskStatus(const std::string& str);
Priority stringToPriority(const std::string& str);