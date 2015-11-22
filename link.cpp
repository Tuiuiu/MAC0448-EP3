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
	//printf ("link %s para %s: is_sniffed_? %d\n", deviceA_.c_str(), deviceB_.c_str(), is_sniffed_);
}

void Link::stop_sniffing()
{
	//printf ("link %s para %s: is_sniffed_? %d\n", deviceA_.c_str(), deviceB_.c_str(), is_sniffed_);
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
	std::cout << "O SRC NAME DOIDO É: " << src_name << std::endl;
	std::cout << "DEVICEA: " << deviceA_->get_name() << std::endl;
	std::cout << "DEVICEB: " << deviceB_->get_name() << std::endl;
	std::cout << "mensagem: " << content.get_message() << std::endl;
	std::cout << "destination ip: " << content.get_destination_ip() << std::endl;
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
		std::cout << "Deu ruim cara... sério... Na hora de mandar coisas no Link" << std::endl;
		//printf("src_name = %s, deviceA_->get_name() = %s, deviceB_->get_name() = %s\n", src_name.c_str(), deviceA_->get_name().c_str(), deviceB_->get_name().c_str());
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
	if (direction == 0) { // do A para o B
		// Formatar uma string
		// Enviar para o arquivo
		// Enviar para a saída padrão
	}
	else if (direction == 1) { // do B para o A
		// Formatar uma string
		// Enviar para o arquivo
		// Enviar para a saída padrão 
	}
	else { // Sério, não sei como faz pra entrar aqui
	}
}