#include <iostream>
#include <vector>
using namespace std;

//S-Single responsibility principle
//A class should have only one reason to change ?


//Open close principle
// A class should be open for extension  but closed for modification ?
// Timed task
// urgent task


//L-Liskove's substitution principle
//I-Interface Segregation Principle

class Notifyables {
	public:
	virtual void sendNotification() = 0;
};
class Task {
	//only responisble for storing the data for a single task
	protected:
		std::string description;
		bool status;
	public:
		Task(const std::string& task): description(task), status(false) {};




		virtual std::string getDescription() {
			return description;
		}
			
		virtual void isCompleted() {
			status = true;	
		}
		virtual bool whatStatus() {
			return status;
		}
};

class UrgentTask: public Task,public Notifyables {
	public:
		UrgentTask(const std::string& task): Task(task) {};
		std::string getDescription() {
		return "Urgent: " + description;
	}

		void sendNotification() {
			std::cout << "Notification:::> " + description;
		}


};

class WrongTask: public Task {
	public:
		WrongTask(const std::string& task): Task(task) {}
		std::string getDescription()
		{
			return "Urgent: "+ description;
		}
		void isComplete() {
			std::cout << "Task complete";
		}
};
//This class is responsible for adding,removing task
class TaskManager {
	private:
		std::vector<Task*> tasks;
	public:
		void addTask(Task* task) {
			tasks.push_back(task);
		}
		// std::string getDescription() {
		// 	return getDescription;
		// }
		void removeTask(int index) {
			if(index >= 0 && index < tasks.size()) {
				tasks.erase(tasks.begin() + index);

		}
		}
		void completed(int index) {
			if(index >= 0 && index < tasks.size()) {
				tasks[index]->isCompleted();
			}
		}

		std::vector<Task*> getTask() {
			return tasks;
		}

		~TaskManager() {
			for(auto task : tasks) {
				delete task;
			}
		}
};

//To display the task or show the task
class Display {
	public:
		static void displayTask(std::vector<Task*> tasks) {
			for(int i = 0 ; i < tasks.size(); i++) {
				std::cout << i << " :" << tasks[i]->getDescription() << " ->" << (tasks[i]->whatStatus() ?  "Complete " : "inComplete") << std::endl;
	}
	}


};
//if you want notification feature in the future for new other type of tasks 
class NotificationManager {
	public:
		static void notify(std::vector<Notifyables*>& tasks) {
			for(int i = 0 ; i < tasks.size(); i++) {
				tasks[i]->sendNotification();
			}
	}

};

int main() {

	std::vector<Task*> tasks;
	std::vector<Notifyables*> notifyablesTask;
	//tasks -> address of type class
	tasks.push_back(new Task("Wash Cloths"));
	tasks.push_back(new UrgentTask("wash cloths"));
	tasks.push_back(new WrongTask("LSP violate"));


	//TaskManager task;
	//task.addTask(new Task("Wash cloths"));
	//task.addTask(new UrgentTask("Do Dishes"));
	//task.completed(1);
	
	tasks[2]->isCompleted();
	notifyablesTask.push_back(dynamic_cast<Notifyables*>(tasks[1]));

	Display::displayTask(tasks);
	NotificationManager::notify(notifyablesTask);

	for(auto task : tasks ) {
		delete task;
	}

	return 0;
}
