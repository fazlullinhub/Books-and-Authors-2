#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

struct Author {
	std::string author_name;
	std::vector<std::string> alternate_name;
	std::string birth_date;
	std::string death_date;
	std::string top_work;
	std::string key;
	std::vector<std::string> top_subjects;
};

void parse(std::string author_name) {
	cpr::Response response = cpr::Get(cpr::Url{ "https://openlibrary.org/search/authors.json?q=" + author_name });
	nlohmann::json json_response = nlohmann::json::parse(response.text);

	std::vector<Author> authors;
	for (auto& obj : json_response["docs"]) {
		Author author;
		author.alternate_name = obj["author_name"];
		author.key = obj["key"];
		author.birth_date = obj["birth_date"];
		author.death_date = obj["death_date"];
		author.key = obj["key"];
		author.top_subjects = obj["top_work"];
	}
}

struct Book {
	std::string title;
	std::string author_name;
	std::string key;
	std::string editions;
	std::string publish_year;
};

void parse(std::string title) {
	cpr::Response response = cpr::Get(cpr::Url{ "https://openlibrary.org/search/books.json?q=" + title });
	nlohmann::json json_response = nlohmann::json::parse(response.text);

	std::vector<Book> books;
	for (auto& obj : json_response["docs"]) {
		Book book;
		book.title = obj["title"];
		book.author_name = obj["author_name"];
		book.key = obj["key"];
		book.editions = obj["editions"];
		book.publish_year = obj["publish_year"];
	}
}

int main() {
	cpr::Response response = cpr::Get(cpr::Url{ "https://openlibrary.org/search.json?" });
	nlohmann::json json_response = nlohmann::json::parse(response.text);
}