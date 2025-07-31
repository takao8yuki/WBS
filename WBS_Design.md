# WBS�A�v���P�[�V�����݌v����

## 1. ER�}�iEntity-Relationship Diagram�j

### �G���e�B�e�B�ƃ����[�V�����V�b�v

```
PROJECT (�v���W�F�N�g)
������ project_id (PK)
������ name
������ description  
������ start_date
������ end_date
������ status
������ created_at

TASK (�^�X�N)
������ task_id (PK)
������ name
������ description
������ start_date
������ end_date
������ duration
������ parent_task_id (FK to TASK)
������ project_id (FK to PROJECT)
������ status
������ priority
������ assigned_to
������ created_at

�����[�V�����V�b�v:
PROJECT (1) -------- (N) TASK
TASK (1) -------- (N) TASK (�T�u�^�X�N)
```

### �G���e�B�e�B�ڍ�

#### PROJECT�i�v���W�F�N�g�j
- **project_id**: �v���W�F�N�g�̈�ӎ��ʎq
- **name**: �v���W�F�N�g��
- **description**: �v���W�F�N�g�̐���
- **start_date**: �v���W�F�N�g�J�n��
- **end_date**: �v���W�F�N�g�I����
- **status**: �v���W�F�N�g�̏�ԁi�v�撆�A�i�s���A�����A�ۗ����j

#### TASK�i�^�X�N�j
- **task_id**: �^�X�N�̈�ӎ��ʎq
- **name**: �^�X�N��
- **description**: �^�X�N�̐���
- **start_date**: �^�X�N�J�n��
- **end_date**: �^�X�N�I����
- **duration**: ��Ɗ��ԁi�����j
- **parent_task_id**: �e�^�X�N��ID�i�K�w�\���p�j
- **project_id**: �����v���W�F�N�g��ID
- **status**: �^�X�N�̏�ԁi���J�n�A�i�s���A�����A�u���b�N���j
- **priority**: �D��x�i��A���A���A�ً}�j
- **assigned_to**: �S���Җ�

## 2. �N���X�}�iClass Diagram�j

### 2.1 ��{�N���X�\��

```
Date
������ -year: int
������ -month: int
������ -day: int
������ +Date()
������ +Date(year, month, day)
������ +toString(): string
������ +isValid(): bool
������ +getCurrentDate(): Date

�񋓌^:
������ ProjectStatus {Planning, InProgress, Completed, OnHold}
������ TaskStatus {NotStarted, InProgress, Completed, Blocked}
������ Priority {Low, Medium, High, Critical}
```

### 2.2 �R�A�N���X

```
Task
������ -taskId: int
������ -name: string
������ -description: string
������ -startDate: Date
������ -endDate: Date
������ -duration: int
������ -parentTaskId: int
������ -projectId: int
������ -status: TaskStatus
������ -priority: Priority
������ -assignedTo: string
������ -subTasks: vector<Task>
������ +addSubTask(task: Task): void
������ +removeSubTask(taskId: int): bool
������ +findSubTask(taskId: int): Task*
������ +updateTask(): void
������ +calculateDuration(): void
������ +toXML(): string
������ +fromXML(xmlData: string): void

Project
������ -projectId: int
������ -name: string
������ -description: string
������ -startDate: Date
������ -endDate: Date
������ -status: ProjectStatus
������ -tasks: vector<Task>
������ +addTask(task: Task): void
������ +removeTask(taskId: int): bool
������ +findTask(taskId: int): Task*
������ +updateProject(): void
������ +getCompletionPercentage(): double
������ +updateProjectStatus(): void
������ +toXML(): string
������ +fromXML(xmlData: string): void
```

### 2.3 �Ǘ��N���X

```
XMLManager
������ -filePath: string
������ +saveToXML(projects: vector<Project>): bool
������ +loadFromXML(projects: vector<Project>): bool
������ +validateXML(xmlContent: string): bool
������ +createBackup(): bool
������ +escapeXML(text: string): string
������ +unescapeXML(xmlText: string): string

WBSManager
������ -projects: vector<Project>
������ -xmlManager: XMLManager
������ -nextProjectId: int
������ -nextTaskId: int
������ -dataFilePath: string
������ +createProject(name: string): int
������ +deleteProject(projectId: int): bool
������ +addTaskToProject(projectId: int, taskName: string): int
������ +loadProjects(): bool
������ +saveProjects(): bool
������ +findProjectsByName(name: string): vector<Project*>
������ +generateProjectReport(projectId: int): string
������ +updateAllProjectStatuses(): void
```

### 2.4 �N���X�֌W
- Project �͕����� Task ���܂� (1:N)
- Task �͕����̃T�u Task �������Ƃ��ł��� (1:N�A���ȎQ��)
- WBSManager �͕����� Project ���Ǘ� (1:N)
- WBSManager �� XMLManager ���g�p (1:1)

## 3. �V�[�P���X�}�iSequence Diagram�j

### 3.1 �v���W�F�N�g�쐬�V�[�P���X

```
User -> WBSManager: createProject(name, description)
WBSManager -> WBSManager: generateNewProjectId()
WBSManager -> Project: new Project(id, name, description)
Project -> Project: initialize()
WBSManager -> WBSManager: projects.push_back(project)
WBSManager -> XMLManager: saveToXML(projects)
XMLManager -> XMLManager: generateProjectsXML(projects)
XMLManager -> XMLFile: write XML data
XMLFile -> XMLManager: success/failure
XMLManager -> WBSManager: save result
WBSManager -> User: project ID
```

### 3.2 �^�X�N�ǉ��V�[�P���X

```
User -> WBSManager: addTaskToProject(projectId, taskName, description)
WBSManager -> WBSManager: findProject(projectId)
WBSManager -> WBSManager: generateNewTaskId()
WBSManager -> Task: new Task(taskId, taskName, projectId)
Task -> Task: initialize()
WBSManager -> Project: addTask(task)
Project -> Project: tasks.push_back(task)
Project -> Project: updateProjectStatus()
WBSManager -> XMLManager: saveToXML(projects)
XMLManager -> WBSManager: save result
WBSManager -> User: task ID
```

### 3.3 �f�[�^�ǂݍ��݃V�[�P���X

```
User -> WBSManager: loadProjects()
WBSManager -> XMLManager: loadFromXML(projects)
XMLManager -> XMLFile: read XML data
XMLFile -> XMLManager: XML content
XMLManager -> XMLManager: parseProjectsXML(xmlContent)

loop [for each project in XML]
    XMLManager -> Project: new Project()
    Project -> Project: fromXML(projectXML)
    
    loop [for each task in project]
        Project -> Task: new Task()
        Task -> Task: fromXML(taskXML)
        Project -> Project: addTask(task)
    end
    
    XMLManager -> XMLManager: projects.push_back(project)
end

XMLManager -> WBSManager: projects vector
WBSManager -> WBSManager: updateMaxIds()
WBSManager -> User: load result
```

### 3.4 �v���W�F�N�g�󋵍X�V�V�[�P���X

```
User -> WBSManager: updateAllProjectStatuses()

loop [for each project]
    WBSManager -> Project: updateProjectStatus()
    Project -> Project: getCompletedTaskCount()
    
    loop [for each task]
        Project -> Task: isCompleted()
        Task -> Project: completion status
    end
    
    Project -> Project: calculateCompletionPercentage()
    Project -> Project: setStatus(newStatus)
end

WBSManager -> XMLManager: saveToXML(projects)
WBSManager -> User: update complete
```

## 4. XML�f�[�^�\��

### 4.1 �v���W�F�N�gXML�\��

```xml
<?xml version="1.0" encoding="UTF-8"?>
<wbs_projects>
    <project id="1">
        <name>�T���v���v���W�F�N�g</name>
        <description>�e�X�g�p�̃v���W�F�N�g</description>
        <start_date>2024-01-01</start_date>
        <end_date>2024-12-31</end_date>
        <status>InProgress</status>
        <tasks>
            <task id="1">
                <name>���C���^�X�N</name>
                <description>�v���W�F�N�g�̃��C���^�X�N</description>
                <start_date>2024-01-01</start_date>
                <end_date>2024-03-31</end_date>
                <duration>90</duration>
                <parent_task_id>-1</parent_task_id>
                <status>InProgress</status>
                <priority>High</priority>
                <assigned_to>�c�����Y</assigned_to>
                <subtasks>
                    <task id="2">
                        <name>�T�u�^�X�N1</name>
                        <!-- ... -->
                    </task>
                </subtasks>
            </task>
        </tasks>
    </project>
</wbs_projects>
```

## 5. �݌v�̓���

### 5.1 �K�w�\���̃T�|�[�g
- �^�X�N�͐e�q�֌W�������Ƃ��ł���iWBS�\���j
- �T�u�^�X�N�͍ċA�I�ɊǗ������

### 5.2 �f�[�^�i����
- XML�t�@�C���ɂ��f�[�^�ۑ�
- �o�b�N�A�b�v�@�\�t��
- �f�[�^�̑Ó�������

### 5.3 ��ԊǗ�
- �v���W�F�N�g�ƃ^�X�N�̏�Ԃ������X�V
- �������̎����v�Z

### 5.4 �����E���|�[�g�@�\
- ���O�A�S���ҁA��ԁA�D��x�ɂ�錟��
- �v���W�F�N�g���|�[�g�̐���

### 5.5 �g����
- �V�����v���p�e�B�̒ǉ����e��
- �v���O�C���I�ȋ@�\�ǉ����\