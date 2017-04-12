/*
 * nheko Copyright (C) 2017  Konstantinos Sideris <siderisk@auth.gr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include "ChatPage.h"
#include "LoginPage.h"
#include "MatrixClient.h"
#include "RegisterPage.h"
#include "SlidingStackWidget.h"
#include "WelcomePage.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	// Show the welcome page in the main window.
	void showWelcomePage();

	// Show the login page in the main window.
	void showLoginPage();

	// Show the register page in the main window.
	void showRegisterPage();

	// Show the chat page and start communicating with the given access token.
	void showChatPage(QString user_id, QString home_server, QString token);

private:
	// The UI component of the main window.
	Ui::MainWindow *ui_;

	// The initial welcome screen.
	WelcomePage *welcome_page_;

	// The login screen.
	LoginPage *login_page_;

	// The register page.
	RegisterPage *register_page_;

	// A stacked widget that handles the transitions between widgets.
	SlidingStackWidget *sliding_stack_;

	// The main chat area.
	ChatPage *chat_page_;

	// Matrix Client API provider.
	QSharedPointer<MatrixClient> client_;
};

#endif  // MAINWINDOW_H