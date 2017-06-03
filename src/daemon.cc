#include "daemon.h"

Daemon::Daemon():_io_service(),
				 _acceptor(_io_service),
				 incoming_socket(_io_service){
	port = 7262;
}

Daemon::~Daemon(){}

void Daemon::runThreads(int argc, char **argv){
	_thread_group.add_thread(new boost::thread(&Daemon::incomingConnHandler,this));
	_thread_group.join_all();
}

void Daemon::incomingConnHandler(){
	boost::asio::ip::tcp::endpoint incoming_conn_endpoint(boost::asio::ip::tcp::v4(), port);
	_acceptor.open(incoming_conn_endpoint.protocol());
	_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	_acceptor.bind(incoming_conn_endpoint);	
	std::cout<<"Tasq Daemon is now listening on port "<<port<<std::endl;
	while(1){
		_acceptor.listen();
		_acceptor.accept(incoming_socket);
		std::cout<<"Connection from "<<incoming_socket.remote_endpoint().address().to_string()<<":"
				 <<std::to_string(incoming_socket.remote_endpoint().port())<<std::endl;
		std::string message = "OK";
		boost::asio::write(incoming_socket,boost::asio::buffer(&message[0],message.size()));
		incoming_socket.close();
	}
}


int main(int argc, char** argv){
	try{
		Daemon daemon;
		daemon.runThreads(argc, argv);
	}
	catch(boost::system::system_error &e){
		std::cout<<e.what();
	}
	return 0;
}