#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <algorithm>

using namespace std;

class Quiz {
public:
	vector <string> correctAnswers;
	vector <string> userAnswers;
	vector <string> correctChoices;
	vector <int> questionIndexes; 

	void setDetails(int score, int rightQ, int wrongQ, int scoreMCQ, int scoreTFQ, int scoreCQ) {
		_score = score; _rightQ = rightQ; _wrongQ = wrongQ, _scoreMCQ = scoreMCQ, _scoreTFQ = scoreTFQ, _scoreCQ = scoreCQ;
	}
	int getScore() {
		return _score;
	}
	int getMCQScore() {
		return _scoreMCQ;
	}
	int getTFQScore() {
		return _scoreTFQ;
	}
	int getCQScore() {
		return _scoreCQ;
	}
	int getRightAnswersNum() {
		return _rightQ;
	}
	int getWrongAnswersNum() {
		return _wrongQ;
	}

private:
	int _score, _rightQ, _wrongQ, _scoreMCQ, _scoreTFQ, _scoreCQ;
};

class Question {
public:
	
	bool operator == (Question& question) {
		string q1 = this->_question;
		string q2 = question.getQuestion();
		transform(q1.begin(), q1.end(), q1.begin(), ::tolower); 
		transform(q2.begin(), q2.end(), q2.begin(), ::tolower);
		if (q1 == q2) {
			return true;
		}
		else {
			return false;
		}
	}
	
	string getQuestion() {
		return _question;
	}
	
	int getID() {
		return _ID;
	}
	
	string getAnswer() {
		return _answer;
	}
	
	virtual void setQuestionAndAnswer() {
	}
	
	virtual bool readQuestionFromFile() {
		return true;
	}
protected:
	string _question, _answer, temp;
	int _ID, counter = 1, n = 0; 
						
};

class MCQuestion : public Question {
public:
	MCQuestion(int ID) {
		_ID = ID;
	}

	
	string getChoices(int n) {
		switch (n) {
		case 1:
			return _answer;
			break;
		case 2:
			return _choice2;
			break;
		case 3:
			return _choice3;
			break;
		case 4:
			return _choice4;
			break;
		}
	}

	void setQuestionAndAnswer(string q, string ans, string c2, string c3, string c4) {
		_question = q;
		_answer = ans;
		_choice2 = c2;
		_choice3 = c3;
		_choice4 = c4;
	}

	bool readQuestionFromFile(string fileName, int line) {
		ifstream QFile;
		QFile.open(fileName.c_str());
		while (getline(QFile, temp)) {
			if (counter >= line) {
				switch (n) {
				case 1:
					_question = temp;
					break;
				case 2:
					_answer = temp;
					break;
				case 3:
					_choice2 = temp;
					break;
				case 4:
					_choice3 = temp;
					break;
				case 5:
					_choice4 = temp;
					break;
				}
				n++;
			}
			if (n == 6) {
				break;
			}
			counter++;
		}
		return true;
	}
private:
	string _choice2;
	string _choice3;
	string _choice4;
};

class TFQuestion : public Question {
public:
	TFQuestion(int ID) {
		_ID = ID;
	}

	void setQuestionAndAnswer(string q, string ans) {
		_question = q;
		_answer = ans;
	}

	bool readQuestionFromFile(string fileName, int line) {
		ifstream QFile;
		QFile.open(fileName.c_str());
		while (getline(QFile, temp)) {
			if (counter >= line) {
				switch (n) {
				case 1:
					_question = temp;
					break;
				case 2:
					_answer = temp;
					break;
				}
				n++;
			}
			if (n == 3) {
				break;
			}
			counter++;
		}
		
		if (_answer == "true" || _answer == "false") {
			return true;
		}
		else {
			return false;
		}

	}
};

class CQuestion : public Question {
public:
	CQuestion(int ID) {
		_ID = ID;
	}

	void setQuestionAndAnswer(string q, string ans) {
		_question = q;
		_answer = ans;
	}

	bool readQuestionFromFile(string fileName, int line) {
		ifstream QFile;
		QFile.open(fileName.c_str());
		while (getline(QFile, temp)) {
			if (counter >= line) {
				switch (n) {
				case 1:
					_question = temp;
					break;
				case 2:
					_answer = temp;
					break;
				}
				n++;
			}
			if (n == 3) {
				break;
			}
			counter++;
		}
		
		if (_answer != "") {
			return true;
		}
		else {
			return false;
		}
	}
};

class User {
public:
	bool operator == (User& otherUser) {
		string user1 = this->_userName;
		string user2 = otherUser.GetUserName();
		transform(user1.begin(), user1.end(), user1.begin(), ::tolower); // This is to convert the usernames to lower case
		transform(user2.begin(), user2.end(), user2.begin(), ::tolower);
		if (user1 == user2) {
			return true;
		}
		else {
			return false;
		}
	}

	void PrintInfo() {
		cout << _fName << "\t\t" << _lName << "\t\t" << _userName << "\t\t" << _role << endl;
	}
	string GetUserName() {
		return _userName;
	}
	string GetPassword() {
		return _password;
	}
	void setFName(string name) {
		_fName = name;
	}
	void setLName(string name) {
		_lName = name;
	}
	void setPassword(string Password) {
		_password = Password;
	}
	string GetFName() {
		return _fName;
	}
	string GetLName() {
		return _lName;
	}
protected:
	string _userName, _password, _fName, _lName, _role;
};

class Admin : public User {
public:
	Admin(string userName, string password, string fName, string lName) {
		_userName = userName; _password = password; _fName = fName; _lName = lName;
		_role = "admin";
	}
private:

};

class Player : public User {
public:
	vector <Quiz> quizzesTaken;

	Player(string userName, string password, string fName, string lName) {
		_userName = userName; _password = password; _fName = fName; _lName = lName;
		_role = "player";
	}
	void AddQuiz(Quiz quiz) {
		quizzesTaken.push_back(quiz);
	}
	int getNumOfQuizzes() {
		return quizzesTaken.size();
	}
};


vector <MCQuestion> allMCQ;
vector <TFQuestion> allTFQ; 
vector <CQuestion> allCQ; 

vector <Admin> allAdmin; 
vector <Player> allPlayer; 


string fileName;
int IDs = 0;
int currentUser; 
string correctChoice;


void LoadQuestions() {
	string name, temp;
	int line = 1, typeLine = 1;
	char failChoice;
	bool fail, repeated;
	ifstream QFile;
	QFile.open(fileName.c_str());

	
	if (QFile.fail()) {
		do {
			system("CLS");
			fail = false;
			cout << "There is no question file found. Would you like to:" << endl << "	[1] Enter a file name to load questions from";
			cout << endl << "	[2] Exit" << endl << "Your choice: ";
			cin >> failChoice;
			while (failChoice != '1' && failChoice != '2') {
				cout << endl << "Incorrect input. Please re-enter your choice: ";
				cin >> failChoice;
			}
			switch (failChoice) {
			case '1':
				cout << endl << "Enter the name of the file: ";
				cin >> name;
				fileName = name + ".txt";
				QFile.open(fileName.c_str());
				if (QFile.fail()) {
					fail = true;
				}
				break;
			case '2':
				exit(1);
				break;
			}
		} while (fail == true);
	}

	
	while (getline(QFile, temp)) {
		repeated = false;
		if (line == typeLine) {
			if (temp == "MCQ") {
				typeLine += 6;
				IDs++;
				MCQuestion newMCQ(IDs);
				if (newMCQ.readQuestionFromFile(fileName, line)) {
					
					for (unsigned int i = 0; i < allMCQ.size(); i++) {
						if ((newMCQ == allMCQ[i])) {
							repeated = true;
						}
					}
					if (repeated == false) {
						allMCQ.push_back(newMCQ);
					}
				}
			}
			else if (temp == "TF") {
				typeLine += 3;
				IDs++;
				TFQuestion newTFQ(IDs);
				if (newTFQ.readQuestionFromFile(fileName, line)) {
					
					for (unsigned int i = 0; i < allTFQ.size(); i++) {
						if ((newTFQ == allTFQ[i])) {
							repeated = true;
						}
					}
					if (repeated == false) {
						allTFQ.push_back(newTFQ);
					}
				}
				else {
					cout << "There is an error in one of the TF questions.\nFile has only loaded until the previous question.\n\n";
					break;
				}
			}
			else if (temp == "COMPLETE") {
				typeLine += 3;
				IDs++;
				CQuestion newCQ(IDs);
				if (newCQ.readQuestionFromFile(fileName, line)) {
					
					for (unsigned int i = 0; i < allCQ.size(); i++) {
						if ((newCQ == allCQ[i])) {
							repeated = true;
						}
					}
					if (repeated == false) {
						allCQ.push_back(newCQ);
					}
				}
				else {
					cout << "There is an error in one of the Complete questions.\nFile has only loaded until the previous question.\n\n";
					break;
				}
				
			}
			else {
				cout << "There is an error in the question type on line " << line << ".\nThe question type written is: " << temp << endl << endl;
				break;
			}
		}
		line++;
	}
	QFile.close();
}


char PrintMCQ(int index, bool game) {
	bool done, choices[4];
	int num, character = 97; 
	char answer;

	cout << allMCQ[index].getQuestion() << endl;
	done = false;
	for (int x = 0; x < 4; x++) {
		choices[x] = false;
	}
	while (done == false) {
		num = rand() % 4 + 1;
		if (choices[num - 1] == false) { 
			if (num == 1) {
				if (game == false) { cout << "*"; }	
				answer = (char)character;
				correctChoice = allMCQ[index].getChoices(num);
			}
			cout << "[" << (char)character << "] ";
			cout << allMCQ[index].getChoices(num);
			cout << "   ";
			choices[num - 1] = true; 
			character++;
		}
		for (int j = 0; j < 4; j++) {
			done = true;
			if (choices[j] == false) {
				done = false;
				break;
			}
		}
	}
	cout << endl << endl;

	return answer;
}


void ViewAllQuestions() {
	char choice;
	int totalQ = allMCQ.size() + allCQ.size() + allTFQ.size();
	cout << "Number of questions available: " << totalQ << endl;
	cout << "------------------------------------\n";
	cout << "MC Questions list (Total: " << allMCQ.size() << " Questions)\n";
	cout << "------------------------------------\n";
	if (allMCQ.size() > 0) {
		for (unsigned int i = 0; i < allMCQ.size(); i++) {
			cout << "[" << i + 1 << "] (ID: " << allMCQ[i].getID() << ") ";
			PrintMCQ(i, false);
		}
	}
	cout << "------------------------------------\n";
	cout << "TF Questions list (Total: " << allTFQ.size() << " Questions)\n";
	cout << "------------------------------------\n";
	if (allTFQ.size() > 0) {
		for (unsigned int i = 0; i < allTFQ.size(); i++) {
			cout << "[" << i + 1 << "] (ID: " << allTFQ[i].getID() << ") ";
			cout << allTFQ[i].getQuestion();
			cout << " (Answer: " << allTFQ[i].getAnswer() << ")\n\n";
		}
	}
	cout << "------------------------------------\n";
	cout << "Complete Questions list (Total: " << allCQ.size() << " Questions)\n";
	cout << "------------------------------------\n";
	if (allCQ.size() > 0) {
		for (unsigned int i = 0; i < allCQ.size(); i++) {
			cout << "[" << i + 1 << "] (ID: " << allCQ[i].getID() << ") ";
			cout << allCQ[i].getQuestion();
			cout << " (Answer: " << allCQ[i].getAnswer() << ")\n\n";
		}
	}

	system("CLS");
}


void AddNewQuestion() {
	char qType;
	string question, answer, c2, c3, c4;
	bool repeated = false;
	cout << "What type of question would you like to add?\n	[1] MCQ \n	[2] T/F \n	[3] Complete \nYour choice: ";
	cin >> qType;
	
	while (qType != '1' && qType != '2' && qType != '3') {
		cout << "\nInvalid Choice. Enter your choice again : ";
		cin >> qType;
	}

	cout << endl << "Enter the question: ";
	cin.ignore();
	getline(cin, question);

	
	if (qType == '1') {
		cout << "The correct choice: ";
		getline(cin, answer);
		cout << "Second choice: ";
		getline(cin, c2);
		cout << "Third choice: ";
		getline(cin, c3);
		cout << "Fourth choice: ";
		getline(cin, c4);
		IDs++;
		MCQuestion newMCQ(IDs);
		newMCQ.setQuestionAndAnswer(question, answer, c2, c3, c4);
		
		for (unsigned int i = 0; i < allMCQ.size(); i++) {
			if ((newMCQ == allMCQ[i])) {
				repeated = true;
			}
		}
		if (repeated == false) {
			allMCQ.push_back(newMCQ);
		}
		else {
			cout << "\nThis question is a duplicate, hence it won't be added.\n";
		}

		
	}
	else if (qType == '2') {
		cout << "The correct answer: ";
		getline(cin, answer);
		IDs++;
		TFQuestion newTFQ(IDs);
		newTFQ.setQuestionAndAnswer(question, answer);
		
		for (unsigned int i = 0; i < allTFQ.size(); i++) {
			if ((newTFQ == allTFQ[i])) {
				repeated = true;
			}
		}
		if (repeated == false) {
			allTFQ.push_back(newTFQ);
		}
		else {
			cout << "\nThis question is a duplicate, hence it won't be added.\n";
		}

	}
	else if (qType == '3') {
		cout << "The correct answer: ";
		getline(cin, answer);
		IDs++;
		CQuestion newCQ(IDs);
		newCQ.setQuestionAndAnswer(question, answer);
		
		for (unsigned int i = 0; i < allCQ.size(); i++) {
			if ((newCQ == allCQ[i])) {
				repeated = true;
			}
		}
		if (repeated == false) {
			allCQ.push_back(newCQ);
		}
		else {
			cout << "\nThis question is a duplicate, hence it won't be added.\n";
		}
	}
	system("pause");
	system("CLS");
}


void NewQuiz() {
	if (allMCQ.size() >= 3 && allTFQ.size() >= 2 && allCQ.size() >= 1) {
		Quiz newQuiz; 
		int scoreMCQ = 0, scoreTFQ = 0, scoreCQ = 0;
		char ansMCQ, correctAnswer;
		string answer;
		int num = 1, randIndex, wrong = 0, right = 0, score = 0;
		int takenMCQ[3] = { -1, -1, -1 }, takenTFQ[2] = { -1, -1 }; 

		
		for (int i = 0; i < 3; i++) {
			randIndex = rand() % allMCQ.size() + 0; 
			for (int j = 0; j < 3; j++) {
				if (takenMCQ[j] == randIndex) {
					randIndex = rand() % allMCQ.size() + 0;
					j = -1;
				}
			}
			takenMCQ[i] = randIndex;
			newQuiz.questionIndexes.push_back(randIndex);
			cout << "Question " << num << " :" << endl;
			correctAnswer = PrintMCQ(randIndex, true);
			newQuiz.correctChoices.push_back(correctChoice);
			cout << endl << "Your answer: ";
			cin >> ansMCQ;


			string userAns(1, ansMCQ), correctAns(1, correctAnswer); 
			newQuiz.userAnswers.push_back(userAns);
			newQuiz.correctAnswers.push_back(correctAns);

			if (ansMCQ == correctAnswer) {
				cout << endl << "Your answer is correct!" << endl << endl;
				right++;
				score += 1; 
				scoreMCQ += 1;
			}
			else {
				cout << endl << "Incorrect! The correct answer is " << correctAnswer << endl << endl;
				wrong++;
			}
			num++;
			cout << " --------------------------------------- " << endl;
		}
		
		for (int i = 0; i < 2; i++) {
			randIndex = rand() % allTFQ.size() + 0; 
			for (int j = 0; j < 2; j++) { 
				if (takenTFQ[j] == randIndex) {
					randIndex = rand() % allTFQ.size() + 0;
					j = -1;
				}
			}
			takenTFQ[i] = randIndex;
			newQuiz.questionIndexes.push_back(randIndex);
			cout << "Question " << num << " :" << endl;
			cout << allTFQ[randIndex].getQuestion() << endl << "Your answer: ";
			cin >> answer;

			newQuiz.userAnswers.push_back(answer);
			newQuiz.correctAnswers.push_back(allTFQ[randIndex].getAnswer());

			if (answer == allTFQ[randIndex].getAnswer()) {
				cout << endl << "Your answer is correct!" << endl << endl;
				right++;
				score += 2; 
				scoreTFQ += 2;
			}
			else {
				cout << endl << "Incorrect! The correct answer is " << allTFQ[randIndex].getAnswer() << endl << endl;
				wrong++;
			}
			num++;
			cout << " --------------------------------------- " << endl;
		}
		
		cout << "Question " << num << " :" << endl;
		randIndex = rand() % allCQ.size() + 0;
		newQuiz.questionIndexes.push_back(randIndex);
		cout << allCQ[randIndex].getQuestion() << endl << "Your answer: ";
		cin >> answer;

		newQuiz.userAnswers.push_back(answer);
		newQuiz.correctAnswers.push_back(allCQ[randIndex].getAnswer());

		if (answer == allCQ[randIndex].getAnswer()) {
			cout << endl << "Your answer is correct!" << endl << endl;
			right++;
			score += 3; 
			scoreCQ += 3;
		}
		else {
			cout << endl << "Incorrect! The correct answer is " << allCQ[randIndex].getAnswer() << endl << endl;
			wrong++;
		}
		cout << " --------------------------------------- " << endl;
		cout << "Score : " << score << "/10\n";
		cout << "Number of right answers: " << right << endl;
		cout << "Number of wrong answers: " << wrong << endl << endl;
		newQuiz.setDetails(score, right, wrong, scoreMCQ, scoreTFQ, scoreCQ);
		allPlayer[currentUser].AddQuiz(newQuiz);
	}
	else {
		cout << "You should have at least 3 MCQ, 2 TF, and 1 Complete question to start the quiz.\nPlease add more questions.\n";
	}
	system("pause"); 
	system("CLS"); 
}

void ScoreStatistics() {
	int num = allPlayer[currentUser].getNumOfQuizzes(), userScore;
	int highest = 0, lowest = 100;
	float sum = 0.0, avgScore = 0.0, sumMC = 0.0, avgMCQScore = 0.0, sumTF = 0.0, avgTFQScore = 0.0, sumC = 0.0, avgCQScore = 0.0;
	if (num > 0) {
		for (int i = 0; i < num; i++) {
			userScore = allPlayer[currentUser].quizzesTaken[i].getScore();
			if (userScore > highest) {
				highest = userScore;
			}
			if (userScore < lowest) {
				lowest = userScore;
			}
			sum += userScore;
			sumMC += allPlayer[currentUser].quizzesTaken[i].getMCQScore();
			sumTF += allPlayer[currentUser].quizzesTaken[i].getTFQScore();
			sumC += allPlayer[currentUser].quizzesTaken[i].getCQScore();
		}
		avgScore = sum / num;
		avgMCQScore = sumMC / num;
		avgTFQScore = sumTF / num;
		avgCQScore = sumC / num;
		cout << "Your score statistics per quiz:\n";
		cout << "\t- Number of Quizzes taken: " << num << endl;
		cout << "\t- Highest quiz score: " << highest << endl;
		cout << "\t- Lowest quiz score: " << lowest << endl;
		cout << "\t- Average quiz score: " << avgScore << "/10" << endl;
		cout << "Your score statistics per question type:\n";
		cout << "\t- Number of MC questions: " << num * 3 << endl;
		cout << "\t- Number of Complete questions: " << num * 1 << endl;
		cout << "\t- Number of T/F questions: " << num * 2 << endl;
		cout << "\t- Average grade for MC quetions: " << avgMCQScore << endl;
		cout << "\t- Average grade for Complete quetions: " << avgCQScore << endl;
		cout << "\t- Average grade for T/F quetions: " << avgTFQScore << endl << endl;
	}
	else {
		cout << "You haven't taken any quizzes yet.\n\n";
	}
	system("pause");
}


void DisplayAllScores() {
	int num = allPlayer[currentUser].getNumOfQuizzes();
	if (num > 0) {
		cout << "The total number of quizzes taken: " << num << endl;
		cout << " -------------------------------- \n";
		for (int i = 0; i < num; i++) {
			cout << "Quiz " << i + 1 << " : \n";
			cout << "\t- Score: " << allPlayer[currentUser].quizzesTaken[i].getScore() << "/10" << endl;
			cout << "\t- Number of right answers: " << allPlayer[currentUser].quizzesTaken[i].getRightAnswersNum() << endl;
			cout << "\t- Number of wrong answers: " << allPlayer[currentUser].quizzesTaken[i].getWrongAnswersNum() << endl;
			cout << "----------------------------\n";
		}
	}
	else {
		cout << "You haven't taken any quizzes yet.\n\n";
	}
	system("pause");
}


void UpdateName(string role) {
	string fName, lName, password;
	cout << "Enter the new first name: ";
	cin.ignore();
	getline(cin, fName);
	cout << "Enter the new last name: ";
	getline(cin, lName);
	cout << "Enter the new password: ";
	getline(cin, password);
	if (role == "player") {
		allPlayer[currentUser].setFName(fName);
		allPlayer[currentUser].setLName(lName);
		allPlayer[currentUser].setPassword(password);
	}
	else {
		allAdmin[currentUser].setFName(fName);
		allAdmin[currentUser].setLName(lName);
		allAdmin[currentUser].setPassword(password);
	}
	system("pause");
}


void PlayerMenu() {
	char choice;
	bool backToLogin = false;
	while (backToLogin == false) {
		system("CLS");
		cout << "Welcome " << allPlayer[currentUser].GetFName() << " " << allPlayer[currentUser].GetLName() << " (PLAYER), please choose from the following options:" << endl
			<< "\t[1] Switch accounts" << endl
			<< "\t[2] Update your name" << endl
			<< "\t[3] Start a new quiz" << endl
			<< "\t[4] Display your scores statistics" << endl
			<< "\t[5] Display all your scores" << endl
			<< "\t[6] Exit the program" << endl
			<< "Your choice: ";
		cin >> choice;
		system("CLS");
		switch (choice) {
		case '1':
			backToLogin = true;
			break;
		case '2':
			UpdateName("player");
			break;
		case '3':
			NewQuiz();
			break;
		case '4':
			ScoreStatistics();
			break;
		case '5':
			DisplayAllScores();
			break;
		case '6':
			exit(1);
			break;
		default:
			cout << "\nInvalid Input.\n\n";
			break;
		}
	}
}


void AdminMenu() {
	string newFile; 
	char choice;
	bool backToLogin = false;
	while (backToLogin == false) {
		system("CLS");
		cout << "Welcome " << allAdmin[currentUser].GetFName() << " " << allAdmin[currentUser].GetLName() << " (ADMIN), please choose from the following options:" << endl
			<< "\t[1] Switch accounts" << endl
			<< "\t[2] Update your name" << endl
			<< "\t[3] View all questions" << endl
			<< "\t[4] Add new question" << endl
			<< "\t[5] Exit the program" << endl
			<< "Your choice: ";
		cin >> choice;
		system("CLS");
		switch (choice) {
		case '1':
			backToLogin = true;
			break;
		case '2':
			UpdateName("admin");
			break;
		case '3':
			ViewAllQuestions();
			break;
		case '4':
			AddNewQuestion();
			break;
		case '5':
			exit(1);
			break;
		default:
			cout << "\nInvalid Input.\n\n";
			break;
		}
	}
}


void LoginPage() {
	string userName, password;
	while (true) {
		bool admin = false, player = false;
		cout << "*******************************************************************" << endl
			<< "\t\tWelcome to the Quiz game program " << endl
			<< "*******************************************************************" << endl;
		cin.ignore();
		cout << "Enter your Username: ";
		getline(cin, userName);
		transform(userName.begin(), userName.end(), userName.begin(), ::tolower);
		cout << "Enter your password: ";
		getline(cin, password);
		transform(password.begin(), password.end(), password.begin(), ::tolower);
		
		for (int i = 0; i < allAdmin.size(); i++) {
			if (userName == allAdmin[i].GetUserName()) {
				if (password == allAdmin[i].GetPassword()) {
					admin = true;
					currentUser = i;
				}
			}
		}
		
		for (int i = 0; i < allPlayer.size(); i++) {
			if (userName == allPlayer[i].GetUserName()) {
				if (password == allPlayer[i].GetPassword()) {
					player = true;
					currentUser = i;
				}
			}
		}
		system("CLS");
		if (admin == true) {
			AdminMenu();
		}
		else if (player == true) {
			PlayerMenu();
		}
		else {
			cout << "\nWrong username or password.\n\n";
		}
	}
}

int main()
{
	srand(time(NULL));

	
	Admin defaultAdmin("admin", "admin", "User", "user");
	allAdmin.push_back(defaultAdmin);
	Player defaultPlayer("player", "player", "User", "user");
	allPlayer.push_back(defaultPlayer);

	fileName = "exam2_questions.txt";		
	LoadQuestions();

	LoginPage();

	return 0;
}