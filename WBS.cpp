// WBS.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include "Date.h"
#include "Enums.h"
#include "Task.h"
#include "Project.h"
#include "WBSManager.h"

void displayMenu() {
    std::cout << "\n=== WBS管理システム ===\n";
    std::cout << "1. プロジェクト作成\n";
    std::cout << "2. プロジェクト一覧表示\n";
    std::cout << "3. タスク追加\n";
    std::cout << "4. プロジェクトレポート表示\n";
    std::cout << "5. データ保存\n";
    std::cout << "6. データ読み込み\n";
    std::cout << "7. 終了\n";
    std::cout << "選択してください: ";
}

void createSampleData(WBSManager& wbsManager) {
    std::cout << "サンプルデータを作成中...\n";
    
    // サンプルプロジェクトの作成
    int projectId = wbsManager.createProject("Webサイト開発プロジェクト", 
                                           "新しいWebサイトの開発プロジェクト");
    
    if (projectId > 0) {
        std::cout << "プロジェクト \"Webサイト開発プロジェクト\" が作成されました (ID: " << projectId << ")\n";
        
        // サンプルタスクの追加
        int taskId1 = wbsManager.addTaskToProject(projectId, "要件定義", "プロジェクトの要件を定義する");
        int taskId2 = wbsManager.addTaskToProject(projectId, "設計", "システムの設計を行う");
        int taskId3 = wbsManager.addTaskToProject(projectId, "実装", "システムの実装を行う");
        int taskId4 = wbsManager.addTaskToProject(projectId, "テスト", "システムのテストを行う");
        
        std::cout << "サンプルタスクが追加されました:\n";
        std::cout << "- 要件定義 (ID: " << taskId1 << ")\n";
        std::cout << "- 設計 (ID: " << taskId2 << ")\n";
        std::cout << "- 実装 (ID: " << taskId3 << ")\n";
        std::cout << "- テスト (ID: " << taskId4 << ")\n";
    }
}

int main() {
    WBSManager wbsManager("wbs_data.xml");
    int choice;
    
    std::cout << "WBS管理システムへようこそ！\n";
    
    // サンプルデータの作成
    createSampleData(wbsManager);
    
    while (true) {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::string name, description;
                std::cout << "プロジェクト名を入力してください: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "プロジェクトの説明を入力してください: ";
                std::getline(std::cin, description);
                
                int projectId = wbsManager.createProject(name, description);
                if (projectId > 0) {
                    std::cout << "プロジェクト \"" << name << "\" が作成されました (ID: " << projectId << ")\n";
                } else {
                    std::cout << "プロジェクトの作成に失敗しました。\n";
                }
                break;
            }
            
            case 2: {
                const auto& projects = wbsManager.getProjects();
                std::cout << "\n=== プロジェクト一覧 ===\n";
                if (projects.empty()) {
                    std::cout << "プロジェクトが登録されていません。\n";
                } else {
                    for (const auto& project : projects) {
                        std::cout << "ID: " << project.getProjectId() 
                                  << ", 名前: " << project.getName()
                                  << ", 状態: " << projectStatusToString(project.getStatus())
                                  << ", タスク数: " << project.getTaskCount() << "\n";
                    }
                }
                break;
            }
            
            case 3: {
                int projectId;
                std::string taskName, description;
                std::cout << "プロジェクトIDを入力してください: ";
                std::cin >> projectId;
                std::cout << "タスク名を入力してください: ";
                std::cin.ignore();
                std::getline(std::cin, taskName);
                std::cout << "タスクの説明を入力してください: ";
                std::getline(std::cin, description);
                
                int taskId = wbsManager.addTaskToProject(projectId, taskName, description);
                if (taskId > 0) {
                    std::cout << "タスク \"" << taskName << "\" が追加されました (ID: " << taskId << ")\n";
                } else {
                    std::cout << "タスクの追加に失敗しました。プロジェクトIDを確認してください。\n";
                }
                break;
            }
            
            case 4: {
                int projectId;
                std::cout << "プロジェクトIDを入力してください: ";
                std::cin >> projectId;
                
                std::string report = wbsManager.generateProjectReport(projectId);
                if (!report.empty()) {
                    std::cout << "\n" << report << "\n";
                } else {
                    std::cout << "プロジェクトが見つかりません。\n";
                }
                break;
            }
            
            case 5: {
                if (wbsManager.saveProjects()) {
                    std::cout << "データが正常に保存されました。\n";
                } else {
                    std::cout << "データの保存に失敗しました。\n";
                }
                break;
            }
            
            case 6: {
                if (wbsManager.loadProjects()) {
                    std::cout << "データが正常に読み込まれました。\n";
                } else {
                    std::cout << "データの読み込みに失敗しました。\n";
                }
                break;
            }
            
            case 7:
                std::cout << "アプリケーションを終了します。\n";
                // 終了前にデータを保存
                if (wbsManager.saveProjects()) {
                    std::cout << "データを保存しました。\n";
                }
                return 0;
                
            default:
                std::cout << "無効な選択です。1-7の範囲で選択してください。\n";
                break;
        }
    }
    
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
