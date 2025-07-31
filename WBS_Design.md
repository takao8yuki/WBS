# WBSアプリケーション設計文書

## 1. ER図（Entity-Relationship Diagram）

### エンティティとリレーションシップ

```
PROJECT (プロジェクト)
├── project_id (PK)
├── name
├── description  
├── start_date
├── end_date
├── status
└── created_at

TASK (タスク)
├── task_id (PK)
├── name
├── description
├── start_date
├── end_date
├── duration
├── parent_task_id (FK to TASK)
├── project_id (FK to PROJECT)
├── status
├── priority
├── assigned_to
└── created_at

リレーションシップ:
PROJECT (1) -------- (N) TASK
TASK (1) -------- (N) TASK (サブタスク)
```

### エンティティ詳細

#### PROJECT（プロジェクト）
- **project_id**: プロジェクトの一意識別子
- **name**: プロジェクト名
- **description**: プロジェクトの説明
- **start_date**: プロジェクト開始日
- **end_date**: プロジェクト終了日
- **status**: プロジェクトの状態（計画中、進行中、完了、保留中）

#### TASK（タスク）
- **task_id**: タスクの一意識別子
- **name**: タスク名
- **description**: タスクの説明
- **start_date**: タスク開始日
- **end_date**: タスク終了日
- **duration**: 作業期間（日数）
- **parent_task_id**: 親タスクのID（階層構造用）
- **project_id**: 所属プロジェクトのID
- **status**: タスクの状態（未開始、進行中、完了、ブロック中）
- **priority**: 優先度（低、中、高、緊急）
- **assigned_to**: 担当者名

## 2. クラス図（Class Diagram）

### 2.1 基本クラス構造

```
Date
├── -year: int
├── -month: int
├── -day: int
├── +Date()
├── +Date(year, month, day)
├── +toString(): string
├── +isValid(): bool
└── +getCurrentDate(): Date

列挙型:
├── ProjectStatus {Planning, InProgress, Completed, OnHold}
├── TaskStatus {NotStarted, InProgress, Completed, Blocked}
└── Priority {Low, Medium, High, Critical}
```

### 2.2 コアクラス

```
Task
├── -taskId: int
├── -name: string
├── -description: string
├── -startDate: Date
├── -endDate: Date
├── -duration: int
├── -parentTaskId: int
├── -projectId: int
├── -status: TaskStatus
├── -priority: Priority
├── -assignedTo: string
├── -subTasks: vector<Task>
├── +addSubTask(task: Task): void
├── +removeSubTask(taskId: int): bool
├── +findSubTask(taskId: int): Task*
├── +updateTask(): void
├── +calculateDuration(): void
├── +toXML(): string
└── +fromXML(xmlData: string): void

Project
├── -projectId: int
├── -name: string
├── -description: string
├── -startDate: Date
├── -endDate: Date
├── -status: ProjectStatus
├── -tasks: vector<Task>
├── +addTask(task: Task): void
├── +removeTask(taskId: int): bool
├── +findTask(taskId: int): Task*
├── +updateProject(): void
├── +getCompletionPercentage(): double
├── +updateProjectStatus(): void
├── +toXML(): string
└── +fromXML(xmlData: string): void
```

### 2.3 管理クラス

```
XMLManager
├── -filePath: string
├── +saveToXML(projects: vector<Project>): bool
├── +loadFromXML(projects: vector<Project>): bool
├── +validateXML(xmlContent: string): bool
├── +createBackup(): bool
├── +escapeXML(text: string): string
└── +unescapeXML(xmlText: string): string

WBSManager
├── -projects: vector<Project>
├── -xmlManager: XMLManager
├── -nextProjectId: int
├── -nextTaskId: int
├── -dataFilePath: string
├── +createProject(name: string): int
├── +deleteProject(projectId: int): bool
├── +addTaskToProject(projectId: int, taskName: string): int
├── +loadProjects(): bool
├── +saveProjects(): bool
├── +findProjectsByName(name: string): vector<Project*>
├── +generateProjectReport(projectId: int): string
└── +updateAllProjectStatuses(): void
```

### 2.4 クラス関係
- Project は複数の Task を含む (1:N)
- Task は複数のサブ Task を持つことができる (1:N、自己参照)
- WBSManager は複数の Project を管理 (1:N)
- WBSManager は XMLManager を使用 (1:1)

## 3. シーケンス図（Sequence Diagram）

### 3.1 プロジェクト作成シーケンス

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

### 3.2 タスク追加シーケンス

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

### 3.3 データ読み込みシーケンス

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

### 3.4 プロジェクト状況更新シーケンス

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

## 4. XMLデータ構造

### 4.1 プロジェクトXML構造

```xml
<?xml version="1.0" encoding="UTF-8"?>
<wbs_projects>
    <project id="1">
        <name>サンプルプロジェクト</name>
        <description>テスト用のプロジェクト</description>
        <start_date>2024-01-01</start_date>
        <end_date>2024-12-31</end_date>
        <status>InProgress</status>
        <tasks>
            <task id="1">
                <name>メインタスク</name>
                <description>プロジェクトのメインタスク</description>
                <start_date>2024-01-01</start_date>
                <end_date>2024-03-31</end_date>
                <duration>90</duration>
                <parent_task_id>-1</parent_task_id>
                <status>InProgress</status>
                <priority>High</priority>
                <assigned_to>田中太郎</assigned_to>
                <subtasks>
                    <task id="2">
                        <name>サブタスク1</name>
                        <!-- ... -->
                    </task>
                </subtasks>
            </task>
        </tasks>
    </project>
</wbs_projects>
```

## 5. 設計の特徴

### 5.1 階層構造のサポート
- タスクは親子関係を持つことができる（WBS構造）
- サブタスクは再帰的に管理される

### 5.2 データ永続化
- XMLファイルによるデータ保存
- バックアップ機能付き
- データの妥当性検証

### 5.3 状態管理
- プロジェクトとタスクの状態を自動更新
- 完了率の自動計算

### 5.4 検索・レポート機能
- 名前、担当者、状態、優先度による検索
- プロジェクトレポートの生成

### 5.5 拡張性
- 新しいプロパティの追加が容易
- プラグイン的な機能追加が可能