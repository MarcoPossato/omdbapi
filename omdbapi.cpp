///////////////////////////////////////////
//										 //
// Desenvolvimento em C++				 //
//						  				 //
// Título: Busca Filmes				     //
//						  				 //
// Autor: Marco Possato				     //
//						  				 //
// Data: 25/03/2019       				 //
//						  				 //
///////////////////////////////////////////


#include <iostream>
#include <string>
#include <stdlib.h>
#include <Windows.h>

#include <curl/curl.h>
#include <json/json.h>

int comunica_site(std::string request) {
	// Inicia comunicação com a url
	CURL* curl = curl_easy_init();

	// Monta a URL a ser chamada
	curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

	// Timeout de 10 segundos.
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

	// Status da resposta
	int httpCode(0);
	std::unique_ptr<std::string> httpData(new std::string());

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);

	return httpCode;
}

namespace {
	std::size_t callback(const char* in, std::size_t size,
		std::size_t num, std::string* out)
	{
		const std::size_t totalBytes(size * num);
		out->append(in, totalBytes);
		return totalBytes;
	}
}

int main() {
	bool sair = 0;
	char opcao_usuario;
	std::string nome_filme;
	std::string url_request;
	int i = 0;

	const std::string titulo_search(jsonData["Title"].asString());
	const int year_search(jsonData["Year"].asInt());
	const std::string rated_search(jsonData["Rated"].asString());
	const std::string released_search(jsonData["Released"].asString());
	const std::string runtime_search(jsonData["Runtime"].asString());
	const std::string genre_search(jsonData["Genre"].asString());
	const std::string director_search(jsonData["Director"].asString());
	const std::string writer_search(jsonData["Writer"].asString());
	const std::string actors_search(jsonData["Actors"].asString());
	const std::string plot_search(jsonData["Plot"].asString());
	const std::string language_search(jsonData["Language"].asString());
	const std::string country_search(jsonData["Country"].asString());
	const std::string awards_search(jsonData["Awards"].asString());
	const std::string poster_search(jsonData["Poster"].asString());
	const std::string ratings_search(jsonData["Ratings"].asString());
	const std::string imd_search(jsonData["Internet Movie Database"].asString());
	const int rotten_tomatoes_search(jsonData["Rotten Tomatoes"].asInt());
	const std::string metacritic_search(jsonData["Metacritic"].asString());
	const std::string type_search(jsonData["Type"].asString());
	const std::string dvd_search(jsonData["DVD"].asString());
	const int boxoffive_search(jsonData["BoxOffice"].asInt());
	const std::string production_search(jsonData["Production"].asString());
	const std::string website_search(jsonData["Website"].asString());

	const std::string movie_type(jsonData["Movie"].asString());
	const std::string series_type(jsonData["Series"].asString());
	const std::string episode_type(jsonData["Episode"].asString());

	std::cout << "*----------------------------*" << std::endl;
	std::cout << "* Bem vindo ao Busca Filmes! *" << std::endl;
	std::cout << "*----------------------------*" << std::endl << std::endl;

	// estrutura do programa
	do {
		std::cout << "Pressione a opcao desejada." << std::endl << std::endl << "Pressione h para HELP;" << std::endl <<
			"Pressione s para BUSCAR;" << std::endl << "Pressione t para TIPO;" << std::endl << "Pressione q para SAIR." <<
			std::endl;
		std::cin >> opcao_usuario;

		system("cls");

		switch (opcao_usuario)
		{

			// help
		case 104:
			std::cout << "Bem vindo a AJUDA!" << std::endl << std::endl;
			std::cout << "Voce pode escolher as seguintes opcoes:" << std::endl << std::endl;
			std::cout << "Pressione s para BUSCAR;" << std::endl << "Pressione t para TIPO;" << std::endl << "Pressione q para SAIR." <<
				std::endl;
			system("pause");
			system("cls");
			break;

			// Search
		case 115:
			std::cout << "Busca!" << std::endl;
			std::cout << "Qual filme deseja pesquisar?" << std::endl;

			// tornou-se necessário colocar duas vezes o getline para poder esperar a inserção do nome
			std::getline(std::cin, nome_filme);
			std::getline(std::cin, nome_filme);

			// transforma todos os espaços em +
			do {
				if (nome_filme[i] == 32) {
					nome_filme[i] = 43;
				}
				i++;
			} while (nome_filme[i] != '\0');

			// monta a url a ser enviada
			url_request = "http://www.omdbapi.com/?t" + nome_filme + "&apikey=6d211a10";

			int resultado_search = comunica_site(url_request);

			if (resultado_search == 200)
			{
				// Prepara para ler o arquivo em Json
				Json::Value jsonData;
				Json::Reader jsonReader;

				if (jsonReader.parse(*httpData.get(), jsonData))
				{
					std::cout << "Title: " << titulo_search << std::endl;
					std::cout << "Year: " << year_search << std::endl;
					std::cout << "Rated: " << rated_search << std::endl;
					std::cout << "Released: " << released_search << std::endl;
					std::cout << "Runtime: " << runtime_search << std::endl;
					std::cout << "Genre: " << genre_search << std::endl;
					std::cout << "Director: " << director_search << std::endl;
					std::cout << "Writer: " << writer_search << std::endl;
					std::cout << "Actors: " << actors_search << std::endl;
					std::cout << "Plot: " << plot_search << std::endl;
					std::cout << "Language: " << language_search << std::endl;
					std::cout << "Country: " << country_search << std::endl;
					std::cout << "Awards: " << awards_search << std::endl;
					std::cout << "Poster: " << poster_search << std::endl;
					std::cout << "Ratings: " << ratings_search << std::endl;
					std::cout << "Internet Movie Database: " << imd_search << std::endl;
					std::cout << "Rotten Tomatoes: " << rotten_tomatoes_search << std::endl;
					std::cout << "Metacritic: " << metacritic_search << std::endl;
					std::cout << "Type: " << type_search << std::endl;
					std::cout << "DVD: " << dvd_search << std::endl;
					std::cout << "BoxOffice: " << boxoffive_search << std::endl;
					std::cout << "Production: " << production_search << std::endl;
					std::cout << "Website: " << website_search << std::endl;
				}
				else
				{
					std::cout << "Nao foi possivel carregar as informacoes" << std::endl;
					return 0;
				}
			}
			else
			{
				std::cout << "Sem resposta do site" << std::endl;
				return 0;
			}

			// aguarda confirmação do usuário para prosseguir
			system("pause");
			system("cls");
			break;

			// type
		case 116:
			std::cout << "O tipo pesquisado e:" << std::endl;

			// monta url do request
			url_request = "http://www.omdbapi.com/?type&apikey=6d211a10";

			int resultado_type = comunica_site(url_request);

			if (resultado_type == 200)
			{
				// Prepara para ler o arquivo em Json
				Json::Value jsonData;
				Json::Reader jsonReader;

				if (jsonReader.parse(*httpData.get(), jsonData))
				{
					std::cout << "Type: " << movie_type << std::endl;
					std::cout << "Type: " << series_type << std::endl;
					std::cout << "Type: " << episode_type << std::endl;
				}
				else
				{
					std::cout << "Nao foi possivel carregar as informacoes" << std::endl;
					return 0;
				}
			}
			else
			{
				std::cout << "Sem resposta do site" << std::endl;
				return 0;
			}

			// aguarda confirmação do usuário para prosseguir
			system("pause");
			system("cls");

			break;

			// quit
		case 113:
			std::cout << "Obrigado!!!" << std::endl << "Volte sempre.";
			sair = 1;
			Sleep(2000);
			break;

			// null
		default:
			std::cout << "Opcao invalida." << std::endl << "Por favor, tente novamente." << std::endl;
			Sleep(2000);
			system("cls");
			break;
		}
	} while (!sair);

	return 0;
}