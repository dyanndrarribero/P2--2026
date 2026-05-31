# 🎬 Sistema de Streaming em C — Arquivos Binários

Trabalho da disciplina de **Programação / Estruturas de Dados**  
Universidade Católica de Pernambuco — UNICAP

---

## 👥 Dupla

| Nome       | RA                                              |
|------------|---------------------------------------------------------------------|
| Dyanndra Gabrielly Ribeiro Souza da Silva  | 00000860512
| Crystal de Fátima Barbosa de Melo Silva  | 00000860510                        |

---

## 📋 Descrição

Sistema de gerenciamento de uma plataforma de streaming, implementado em **linguagem C** com manipulação de **dois arquivos binários**:

| Arquivo        | Registro   | Campos principais                                                        |
|----------------|------------|--------------------------------------------------------------------------|
| `videos.bin`   | `Video`    | id, título, gênero, ano, duração, url                                    |
| `usuarios.bin` | `Usuario`  | id, nome, e-mail, **favoritos[]** (vetor de IDs de vídeos), qtd_favoritos |

O campo `favoritos[]` de `Usuario` contém os IDs dos vídeos favoritados, estabelecendo o **relacionamento** entre os dois registros.

---

## 🗂️ Estrutura de Arquivos

```
streaming/
├── structs.h      → definição das structs Video e Usuario
├── usuarios.h     → declarações das funções de usuário
├── usuarios.c     → implementação: CRUD + favoritos + relatório  
├── videos.h       → declarações das funções de vídeo
├── videos.c       → implementação: CRUD de vídeos                
├── main.c         → menu interativo principal                    
├── Makefile       → regras de compilação
├── comandos.txt   → guia de compilação e execução
└── README.md      → este arquivo
```

---

## ⚙️ Funcionalidades

### Vídeos
- ✅ Cadastrar novo vídeo
- ✅ Atualizar dados de um vídeo existente
- ✅ Listar todos os vídeos
- ✅ Buscar vídeo por ID
- ✅ Remover vídeo (cria novo arquivo sem o registro, substitui o antigo)

### Usuários
- ✅ Cadastrar novo usuário
- ✅ Atualizar dados de um usuário existente
- ✅ Listar todos os usuários
- ✅ Buscar usuário por ID
- ✅ Remover usuário (mesmo mecanismo de cópia)
- ✅ Adicionar/remover vídeos da lista de favoritos

### Relatórios
- ✅ **Todos os usuários com os *nomes* dos vídeos favoritados** (não os IDs — faz lookup no arquivo de vídeos)
- ✅ Listagem completa de vídeos

---

## 🔁 Mecanismo de Remoção

A exclusão de registros segue o padrão exigido pelo enunciado:

1. Abre o arquivo original em modo leitura
2. Cria um arquivo temporário em modo escrita
3. Copia todos os registros, **exceto** o que deve ser removido
4. Fecha ambos os arquivos
5. **Remove** o arquivo original (`remove()`)
6. **Renomeia** o temporário para o nome original (`rename()`)

---

## 🚀 Como Compilar e Executar

```bash
# Com Makefile
make
./streaming

# Ou manualmente
gcc -Wall -Wextra -std=c11 -o streaming main.c usuarios.c videos.c
./streaming
```

Consulte o arquivo `comandos.txt` para mais detalhes e sequência de testes.

---

## 📦 Dependências

- GCC (C11 ou superior)
- Nenhuma biblioteca externa — apenas `stdio.h`, `stdlib.h` e `string.h`
