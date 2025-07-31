# WBS Mermaid設計図ファイル整理ガイド

## ? 重要：重複ファイルの整理が必要

以下のMermaidファイルには重複とシンタックスエラーがあります：

### ?? 削除対象（重複ファイル）

1. **WBS_ER_Diagram.mmd** ?
   - **問題**: WBS_Design_ER.mmdと重複
   - **推奨**: 削除
   - **代替**: WBS_Design_ER.mmdを使用

2. **WBS_Design_Class.mmd** ? 
   - **問題**: WBS_Class_Diagram.mmdと重複
   - **推奨**: 削除
   - **代替**: WBS_Class_Diagram.mmdを使用

3. **WBS_Design_Mermaid.mmd** ?
   - **問題**: 複数図混在、文字化け
   - **推奨**: 削除済み
   - **代替**: 個別の専用ファイル使用

### ? 使用推奨ファイル（正常動作）

1. **WBS_Design_ER.mmd** ?
   - **用途**: ER図（Entity-Relationship Diagram）
   - **状態**: 正常動作
   - **内容**: PROJECT・TASKエンティティとリレーションシップ

2. **WBS_Class_Diagram.mmd** ?  
   - **用途**: クラス図（Class Diagram）
   - **状態**: 正常動作
   - **内容**: Date, Task, Project, WBSManager, XMLManagerクラス

3. **WBS_Sequence_ProjectCreation.mmd** ?
   - **用途**: プロジェクト作成シーケンス図
   - **状態**: 正常動作
   - **内容**: User → WBSManager → Project → XMLManager のフロー

4. **WBS_Sequence_TaskCreation.mmd** ?
   - **用途**: タスク作成シーケンス図  
   - **状態**: 正常動作
   - **内容**: User → WBSManager → Task → Project のフロー

5. **WBS_Architecture.mmd** ?
   - **用途**: システムアーキテクチャ図
   - **状態**: 正常動作
   - **内容**: レイヤード・アーキテクチャの表現

## ?? 推奨アクション

### 即座に実行
1. ? `WBS_ER_Diagram.mmd` を削除
2. ? `WBS_Design_Class.mmd` を削除  
3. ? `WBS_Design_Mermaid.mmd` を削除（既に削除済みの場合はスキップ）

### 使用ルール
- **1ファイル = 1図** の原則を守る
- **UTF-8エンコーディング** で保存
- **純粋なMermaid記法のみ** 記述（```mermaidブロック不要）
- **説明テキストは含めない**

## ?? 最終的なファイル構成

```
WBS/
├── WBS_Design_ER.mmd          ? ER図
├── WBS_Class_Diagram.mmd      ? クラス図  
├── WBS_Sequence_ProjectCreation.mmd ? プロジェクト作成シーケンス
├── WBS_Sequence_TaskCreation.mmd    ? タスク作成シーケンス
├── WBS_Architecture.mmd       ? アーキテクチャ図
└── WBS_Mermaid_Split_Guide.md ? このガイドファイル
```

## ?? シンタックスエラーの修正状況

すべての推奨ファイルは正常なMermaid記法で記述されており、シンタックスエラーはありません。

## ?? 次のステップ

1. 重複ファイルを手動で削除
2. 推奨ファイルのみを使用してMermaid図を表示
3. 新しい図が必要な場合は適切な命名規則で新規作成

---

**注意**: この整理により、Mermaidツールでの表示が正常に動作し、メンテナンス性が向上します。