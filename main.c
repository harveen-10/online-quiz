#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 5
#define MAX_QUESTIONS 10
#define MAX_ANSWERS 4

struct Question {
    char question[100];
    char answers[MAX_ANSWERS][50];
    int correctAnswerIndex;
};

struct Category {
    char name[50];
    struct Question questions[MAX_QUESTIONS];
};

int main() {
    // Create an array to store categories
    struct Category categories[MAX_CATEGORIES];

    FILE *file = fopen("quiz_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[1000];
    int categoryIndex = -1;
    int questionIndex = -1;

    int answerIndex = 0;
    char currentCategory[50] = "";

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Category: ")) {
            categoryIndex++;
            questionIndex = -1;
            // Extract the category name and store it in currentCategory
            strcpy(currentCategory, line + strlen("Category: "));
            currentCategory[strcspn(currentCategory, "\n")] = '\0';

            // Check if the category name is different from the previous one
            if (categoryIndex > 0 && strcmp(currentCategory, categories[categoryIndex - 1].name) == 0) {
                // Same category name, so don't increase categoryIndex
                categoryIndex--;
            }
            strcpy(categories[categoryIndex].name, currentCategory);
        }
        else if (strstr(line, "Question: ")) {
            questionIndex++;
            answerIndex = 0; // Reset answerIndex for each question
            strcpy(categories[categoryIndex].questions[questionIndex].question, line + strlen("Question: "));
            categories[categoryIndex].questions[questionIndex].question[strcspn(categories[categoryIndex].questions[questionIndex].question, "\n")] = '\0';
        }
        else if (strstr(line, "Answer: ")) {
            strcpy(categories[categoryIndex].questions[questionIndex].answers[answerIndex], line + strlen("Answer: "));
            categories[categoryIndex].questions[questionIndex].answers[answerIndex][strcspn(categories[categoryIndex].questions[questionIndex].answers[answerIndex], "\n")] = '\0';
            answerIndex++; // Increment answerIndex
        }
        else if (strstr(line, "Correct Answer Index: ")) {
            int correctAnswerIndex;
            if (sscanf(line, "Correct Answer Index: %d", &correctAnswerIndex) == 1) {
                categories[categoryIndex].questions[questionIndex].correctAnswerIndex = correctAnswerIndex;
            }
        }
    }

    fclose(file);
    printf("successful");

    return 0;
}

