#!/usr/bin/env python

import socket

TCP_IP = '192.168.0.52'
TCP_PORT = 5000
BUFFER_SIZE = 1024
MESSAGE = "Hello, World!"

def print_dispositivos():
    print('1- L1')
    print('2- L2')
    print('3- L3')
    print('4- L4')
    print('5- A1')
    print('6- A2')
    print('7- SP1')
    print('8- SP2')
    print('9- SA1')
    print('10- SA2')
    print('11- SA3')
    print('12- SA4')
    print('13- SA5')
    print('14- SA6')

while(1):
    print('Bem-vindo ao servidor central do Trabalho 2')
    print('0- Sair')
    print('1- Ligar um dispositivo')
    print('2- Desligar um dispositivo')
    print('3- Checar sensores')
    print('4- Checar tempratura e umidade')
    print('5- Escolher temperatura')
    opcao = input('Escolha uma das opções: ')

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    if opcao == '1':
        print_dispositivos()
        escolha = input('Escolha um dispositivo: ')
        mensagem = [opcao,escolha]
        s.connect((TCP_IP, TCP_PORT))
        s.sendall(MESSAGE.encode('utf-8'))
        s.sendall(mensagem.encode('utf-8'))
        break
    elif opcao == '2':
        print_dispositivos()
        escolha = input('Escolha um dispositivo: ')
        mensagem = [opcao,escolha]
        s.connect((TCP_IP, TCP_PORT))
        s.send(MESSAGE.encode('utf-8'))
        s.send(mensagem.encode('utf-8'))
        break
    elif opcao == '3':
        s.connect((TCP_IP, TCP_PORT))
        s.send(MESSAGE.encode('utf-8'))
        s.send(mensagem.encode('utf-8'))
        data = s.recv(BUFFER_SIZE)
        data_real = str(data).split()
        print(data_real[0][2:], data_real[1][:6])
        break
    elif opcao == '4':
        s.connect((TCP_IP, TCP_PORT))
        s.send(MESSAGE.encode('utf-8'))
        s.send(mensagem.encode('utf-8'))
        data = s.recv(BUFFER_SIZE)
        data_real = str(data).split()
        print(data_real[0][2:], data_real[1][:6])
        break
    elif opcao == '5':
        s.connect((TCP_IP, TCP_PORT))
        temp = input('Digite a temperatura desejada: ')
        mensagem = [opcao,temp]
        s.send(MESSAGE.encode('utf-8'))
        s.send(mensagem[0].encode('utf-8'))
        s.send(mensagem[1].encode('utf-8'))

        break
    else:
        print('Saindo...')
        break

    s.close()