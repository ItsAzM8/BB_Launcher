// SPDX-FileCopyrightText: Copyright 2024 BBLauncher Project
// SPDX-License-Identifier: GPL-3.0-or-later

#include <filesystem>
#include <iostream>
#include <QApplication>
#include <QCommandLineParser>
#include <QMessageBox>
#include "modules/RunGuard.h"
#include "modules/bblauncher.h"

void customMessageHandler(QtMsgType, const QMessageLogContext&, const QString&) {}

int main(int argc, char* argv[]) {
    qInstallMessageHandler(customMessageHandler);
    std::cout << "SHADPS4 LOG WINDOW\n\n";
    QApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption noGui("n");
    parser.addOption(noGui);
    parser.process(a);
    bool noGUIset = parser.isSet(noGui);

    RunGuard guard("d8976skj86874hkj287960980lkjhfka1#Q$^&*");
    bool noinstancerunning = guard.tryToRun();

    BBLauncher* main_window = new BBLauncher(noGUIset, noinstancerunning);

    if (!noinstancerunning) {
        QMessageBox::warning(nullptr, "BB_Launcher already running",
                             "Only one instance of BB_Launcher can run at a time");
        return 0;
    }

    if (!noGUIset)
        main_window->show();

#ifdef _WIN32
    if (!std::filesystem::exists(std::filesystem::current_path() / "shadPS4.exe")) {
        QMessageBox::warning(
            nullptr, "No shadPS4.exe found",
            "No shadPS4.exe found. Move BB_Launcher.exe next to shadPS4.exe.\n\nMove all other "
            "files/folders in BB_Launcher folder to shadPS4 folder only if you are using a "
            "non-QT "
            "(no GUI) version of shadPS4.");
    } else {
        return a.exec();
    }
#elif defined(__linux__)
    if (!std::filesystem::exists(std::filesystem::current_path() / "Shadps4-qt.AppImage") &&
        !std::filesystem::exists(std::filesystem::current_path() / "Shadps4-sdl.AppImage") &&
        !std::filesystem::exists(std::filesystem::current_path() / "shadps4")) {
        QMessageBox::warning(nullptr, "No Shadps4 App or AppImage found",
                             "No Shadps4 App or AppImage found. Move BB_Launcher app next to "
                             "shadPS4 App or AppImage");
    } else {
        return a.exec();
    }

#elif defined(__APPLE__)
    if (!std::filesystem::exists(std::filesystem::current_path() / "shadps4.app")) {
        QMessageBox::warning(nullptr, "No shadps4 app found",
                             "No shadPS4 app found. Move BB_Launcher app next to shadPS4 install.");
    } else if (!std::filesystem::exists(std::filesystem::current_path() / "shadps4.")) {
        QMessageBox::warning(
            nullptr, "No shadps4 app found",
            "No shadPS4 app found. Move BB_Launcher app and other files next to shadPS4 install");
    } else {
        return a.exec();
    }
#endif
}
