#include <iostream>
#include <fstream>
#include <string>


struct Respondent {
    int age;
    std::string gender;
    std::string education;
    std::string answer;
    Respondent* next;
};

void addQuestionnaire(Respondent*& head);

Respondent* createNode(const Respondent& respondent)
{
    Respondent* newNode = new Respondent;
    newNode->age = respondent.age;
    newNode->gender = respondent.gender;
    newNode->education = respondent.education;
    newNode->answer = respondent.answer;
    newNode->next = nullptr;
    return newNode;
}

void addRespondent(Respondent*& head, const Respondent& respondent)
{
    Respondent* newNode = createNode(respondent);

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Respondent* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void displayRespondents(const Respondent* head)
{
    const Respondent* current = head;

    while (current != nullptr) {
        std::cout << "Age: " << current->age << ", Gender: " << current->gender
            << ", Education: " << current->education << ", Answer: " << current->answer << std::endl;
        current = current->next;
    }
}


void saveDataToFile(const Respondent* head, const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file for writing." << std::endl;
        return;
    }

    const Respondent* current = head;

    while (current != nullptr) {
        file << "Age:" << current->age << std::endl;
        file << "Gender:" << current->gender << std::endl;
        file << "Education:" << current->education << std::endl;
        file << "Answer:" << current->answer << std::endl;
        current = current->next;
    }

    file.close();

    std::cout << "Data has been saved to a file " << filename << "." << std::endl;
}

Respondent* loadDataFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file for reading." << std::endl;
        return nullptr;
    }

    Respondent* head = nullptr;
    std::string line;
    int fieldCount = 0;
    Respondent respondent;

    while (std::getline(file, line)) {
        if (fieldCount == 0) {
            respondent.age = std::stoi(line);
        }
        else if (fieldCount == 1) {
            respondent.gender = line;
        }
        else if (fieldCount == 2) {
            respondent.education = line;
        }
        else if (fieldCount == 3) {
            respondent.answer = line;
            addRespondent(head, respondent);
            fieldCount = -1; // Reset field count for the next respondent
        }
        else {
            std::cerr << "Invalid data format: " << line << std::endl;
            continue;
        }

        fieldCount++;
    }

    file.close();

    std::cout << "Data has been loaded from a file " << filename << "." << std::endl;

    return head;
}



int countAnswers(const Respondent* head, const std::string& gender, int ageLimit, const std::string& education, const std::string& answer)
{
    const Respondent* current = head;
    int count = 0;

    while (current != nullptr) {
        bool ageCondition = false;

        if (gender == "male" && current->age > ageLimit) {
            ageCondition = true;
        }
        else if (gender == "female" && current->age < ageLimit) {
            ageCondition = true;
        }

        if (ageCondition && current->education == education && current->answer == answer) {
            count++;
        }

        current = current->next;
    }

    return count;
}



void addQuestionnaire(Respondent*& head)
{
    Respondent respondent;

    std::cout << "Enter respondent's age: ";
    std::cin >> respondent.age;

    std::cout << "Enter respondent's gender (male/female): ";
    std::cin >> respondent.gender;

    std::cout << "Enter respondent's education level (primary/secondary/higher): ";
    std::cin >> respondent.education;

    std::cout << "Enter respondent's answer (Yes/No): ";
    std::cin >> respondent.answer;

    addRespondent(head, respondent);

    std::cout << "Questionnaire has been added." << std::endl;
}

int main()
{
    Respondent* head = nullptr;
    int choice;

    do {
        std::cout << "1. Add a questionnaire" << std::endl;
        std::cout << "2. Print questionnaires" << std::endl;
        std::cout << "3. Save data to file" << std::endl;
        std::cout << "4. Load data from file" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "6. How many men over 40 years old with higher education answered Yes to the questionnaire" << std::endl;
        std::cout << "7. How many women under the age of 30 with secondary education answered No to the questionnaire" << std::endl;
        std::cout << "8. How many men under the age of 25 with primary education answered Yes to the questionnaire" << std::endl;
        std::cout << "Choose an action: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            addQuestionnaire(head);
            break;
        }

        case 2: {
            std::cout << "Questionnaires of respondents:" << std::endl;
            std::cout << "-------------------" << std::endl;
            displayRespondents(head);
            break;
        }

        case 3: {
            std::string filename;
            std::cout << "Enter the filename to save the data: ";
            std::cin >> filename;
            saveDataToFile(head, filename);
            break;
        }
        case 4: {
            std::string filename;
            std::cout << "Enter the filename to load the data: ";
            std::cin >> filename;
            head = loadDataFromFile(filename);
            break;
        }
        case 5: {
            std::cout << "Exiting the program..." << std::endl;
            break;
        }
        case 6: {
            int count = countAnswers(head, "male", 40, "higher", "Yes");
            std::cout << "Number of men over 40 years old with higher education who answered Yes: " << count << std::endl;
            break;
        }
        case 7: {
            int count = countAnswers(head, "female", 30, "secondary", "No");
            std::cout << "Number of women under the age of 30 with secondary education who answered No: " << count << std::endl;
            break;
        }
        case 8: {
            int count = countAnswers(head, "male", 25, "primary", "Yes");
            std::cout << "Number of men under the age of 25 with primary education who answered Yes: " << count << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        }
    } while (choice != 5);

    return 0;
}