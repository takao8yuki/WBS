#pragma once
#include <string>

// �v���W�F�N�g�̏�Ԃ�\���񋓌^
enum class ProjectStatus {
    Planning,       // �v�撆
    InProgress,     // �i�s��
    Completed,      // ����
    OnHold          // �ۗ���
};

// �^�X�N�̏�Ԃ�\���񋓌^
enum class TaskStatus {
    NotStarted,     // ���J�n
    InProgress,     // �i�s��
    Completed,      // ����
    Blocked         // �u���b�N��
};

// �D��x��\���񋓌^
enum class Priority {
    Low,            // ��
    Medium,         // ��
    High,           // ��
    Critical        // �ً}
};

// �񋓌^�𕶎���ɕϊ����郆�[�e�B���e�B�֐�
std::string projectStatusToString(ProjectStatus status);
std::string taskStatusToString(TaskStatus status);
std::string priorityToString(Priority priority);

// �����񂩂�񋓌^�ɕϊ����郆�[�e�B���e�B�֐�
ProjectStatus stringToProjectStatus(const std::string& str);
TaskStatus stringToTaskStatus(const std::string& str);
Priority stringToPriority(const std::string& str);