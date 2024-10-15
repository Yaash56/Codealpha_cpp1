#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

// Tokenization and preprocessing
std::vector<std::string> tokenize(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        // Convert to lowercase and remove punctuation (basic preprocessing)
        token.erase(std::remove_if(token.begin(), token.end(), ispunct), token.end());
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        tokens.push_back(token);
    }
    return tokens;
}

// Intent Detection (Rule-based for simplicity, can be replaced by ML model)
std::string detectIntent(const std::vector<std::string>& tokens) {
    // Simple keyword-based approach for demo purposes
    if (std::find(tokens.begin(), tokens.end(), "hello") != tokens.end()) {
        return "greeting";
    } else if (std::find(tokens.begin(), tokens.end(), "bye") != tokens.end()) {
        return "goodbye";
    } else if (std::find(tokens.begin(), tokens.end(), "weather") != tokens.end()) {
        return "ask_weather";
    } else if (std::find(tokens.begin(), tokens.end(), "time") != tokens.end()) {
        return "ask_time";
    } else {
        return "unknown";
    }
}

// Simple Sentiment Analysis (positive, negative, neutral)
std::string sentimentAnalysis(const std::string& input) {
    std::vector<std::string> positiveWords = {"happy", "great", "fantastic", "good"};
    std::vector<std::string> negativeWords = {"sad", "bad", "terrible", "angry"};
    
    for (const auto& word : positiveWords) {
        if (input.find(word) != std::string::npos) {
            return "positive";
        }
    }
    
    for (const auto& word : negativeWords) {
        if (input.find(word) != std::string::npos) {
            return "negative";
        }
    }
    
    return "neutral";
}

// Complex Question Answering (Placeholder function, can integrate with AI model like BERT or GPT)
std::string answerComplexQuestion(const std::string& question) {
    // For demo purposes, let's provide a canned response.
    if (question.find("what is ai") != std::string::npos) {
        return "Artificial Intelligence (AI) is the simulation of human intelligence in machines.";
    } else if (question.find("who is einstein") != std::string::npos) {
        return "Albert Einstein was a theoretical physicist who developed the theory of relativity.";
    } else {
        return "Sorry, I don't know the answer to that question.";
    }
}

// Dialogue Management (keeping context)
void manageDialogue(const std::string& input, std::string& lastResponse) {
    if (input == "ask_weather") {
        lastResponse = "The weather is sunny today.";
    } else if (input == "ask_time") {
        lastResponse = "The current time is 2:00 PM.";
    } else if (input == "greeting") {
        lastResponse = "Hello! How can I assist you today?";
    } else if (input == "goodbye") {
        lastResponse = "Goodbye! Have a nice day!";
    } else {
        lastResponse = answerComplexQuestion(input);
    }
}

int main() {
    std::string userInput;
    std::string lastResponse = "";
    
    std::cout << "Chatbot: Hello! How can I help you today?\n";

    while (true) {
        std::cout << "You: ";
        std::getline(std::cin, userInput);

        // Tokenize input
        std::vector<std::string> tokens = tokenize(userInput);

        // Detect intent
        std::string intent = detectIntent(tokens);

        // Perform sentiment analysis
        std::string sentiment = sentimentAnalysis(userInput);
        std::cout << "Sentiment: " << sentiment << "\n";

        // Manage dialogue based on intent
        manageDialogue(intent, lastResponse);

        // Respond to user
        std::cout << "Chatbot: " << lastResponse << std::endl;

        if (intent == "goodbye") {
            break;
        }
    }
}

