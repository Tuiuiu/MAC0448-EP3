#include <iostream>

#include "link.hpp"

void Link::print_test() {
	std::cout << "Duplex-link entre " << deviceA_->get_name() << " e " << deviceB_->get_name() << std::endl;
	std::cout << "    |____ velocidade: " << speed_ << "Mbps" << std::endl;
	std::cout << "    |____ latencia: " << latency_ << "ms" << std::endl;
}

void Link::start_sniffing(std::string file_name)
{
	is_sniffed_ = true;
	sniff_output_ = new std::ofstream;
	sniff_output_->open (file_name);
	(*sniff_output_) << "Sniffing interfaces " << deviceA_->get_name() << " to " << deviceB_->get_name() << ".\n";
}

void Link::stop_sniffing()
{
	if (is_sniffed_)
		sniff_output_->close();
	is_sniffed_ = false;
}

bool Link::links(std::string A, std::string B)
{
	if ((A == deviceA_->get_name() && B == deviceB_->get_name()) || (A == deviceB_->get_name() && B == deviceA_->get_name()))
		return true;
	else
		return false;
}

bool Link::send_datagram(std::string src_name, Datagram content) {
	if(src_name == deviceA_->get_name()) {
		if(processment_a_to_b_ == -1) {
			processment_a_to_b_ = 1000; // Aqui tem que fazer algo do tipo: Calcular o tempo
										// que leva pra enviar o pacote na velocidade do cabo,
										// somando o delay
			content_a_to_b_ = content;
			if (is_sniffed_) {
				print_sniffed_content(0, content);
			}
			return true; // Ou seja, não tem nada dentro do Link do A pro B, então ele
						 // pode enviar. return true = enviando pacote.
		} 
		else { // (processment_a_to_b_ != -1) {
			return false; // Caso tenha alguma coisa passando do A pro B no Link,
						  // então ele pede pro deviceA esperar. Isso significa,
						  // no caso, retornar false.
		}
	} else if(src_name == deviceB_->get_name()) {
		if(processment_b_to_a_ == -1) {
			processment_b_to_a_ = 1000; // Aqui tem que fazer algo do tipo: Calcular o tempo
										// que leva pra enviar o pacote na velocidade do cabo,
										// somando o delay
			content_b_to_a_ = content;
			if (is_sniffed_) {
				print_sniffed_content(1, content);
			}
			return true; // Ou seja, não tem nada dentro do Link do A pro B, então ele
						 // pode enviar. return true = enviando pacote.
		}
		else { // (processment_b_to_a_ != -1) {
			return false; // Caso tenha alguma coisa passando do B pro A no Link,
						  // então ele pede pro deviceA esperar. Isso significa,
						  // no caso, retornar false.
		}
	} 
	else {
		// "Deu ruim cara... sério... Na hora de mandar coisas no Link" << std::endl;
		return false;
	}
}

void Link::network_tick() {
	if (processment_a_to_b_ != -1) { // Se tiver algo a ser processado, roda 1 dt.
		processment_a_to_b_ -= 1;    // Caso não haja, mantém o valor de -1.
	} 

	if (processment_a_to_b_ == 0) {
		// Se, depois de contar mais 1 dt, o tempo é 0, então pode enviar o pacote.
		deviceB_->receive_datagram(content_a_to_b_);
		processment_a_to_b_ = -1;
	}

	if (processment_b_to_a_ != -1) { // Se tiver algo a ser processado, roda 1 dt.
		processment_b_to_a_ -= 1;    // Caso não haja, mantém o valor de -1.
	} 

	if (processment_b_to_a_ == 0) {
		// Se, depois de contar mais 1 dt, o tempo é 0, então pode enviar o pacote.
		deviceA_->receive_datagram(content_b_to_a_);
		processment_b_to_a_ = -1;
	}
	virtual_time_ += 1;
}

void Link::print_sniffed_content(int direction, Datagram content) {
	std::string cabecalho;
	std::string rede;
	std::string transporte;
	std::string aplicacao;
	// if (direction == 0) { // do A para o B
	
	cabecalho = "ID: " + content.get_id() + " Time: " + std::to_string(virtual_time_) 
	+ " Sniffer entre " + deviceA_->get_name() + " e " + deviceB_->get_name() + "\n";
	rede = " |_Camada de Rede: \n   |_ IP Origem: " + content.get_source_ip() 
	+ "\n   |_ IP Destino: " + content.get_destination_ip() 
	+ "\n   |_ Tipo de protocolo de transporte: " + content.get_type();
	transporte = "\n |_Camada de Transporte: \n   |_ Porta da fonte: " 
	+ std::to_string(content.get_source_port()) + "\n   |_ Porta do destino: " 
	+ std::to_string(content.get_destination_port());
	aplicacao = "\n |_|Camada de Aplicação: \n   |_ Conteudo da mensagem: " 
	+ content.get_message() + "\n";
	
	std::cout << cabecalho <<  rede << transporte << aplicacao << std::endl;

	(*sniff_output_) << cabecalho << rede << transporte << aplicacao << ".\n";



		// Formatar uma string
		// Enviar para o arquivo
		// Enviar para a saída padrão
	//}
	//else if (direction == 1) { // do B para o A
		// Formatar uma string
		// Enviar para o arquivo
		// Enviar para a saída padrão 
	//}
	//else { // Sério, não sei como faz pra entrar aqui
	//}
}