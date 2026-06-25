#!/bin/bash

PROG="./analisador_dna"
PASS=0
FAIL=0

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

ok() {
    echo -e "${GREEN}[OK]${NC} $1"
    PASS=$((PASS+1))
}

fail() {
    echo -e "${RED}[FALHOU]${NC} $1"
    echo -e "         esperado: $2"
    echo -e "         obtido:   $3"
    FAIL=$((FAIL+1))
}

run() {
    echo "$1" | $PROG 2>/dev/null
}

check() {
    local desc="$1"
    local input="$2"
    local expected="$3"
    local output
    output=$(run "$input")
    if echo "$output" | grep -qi "$expected"; then
        ok "$desc"
    else
        fail "$desc" "$expected" "$(echo "$output" | tr '\n' ' ' | cut -c1-80)"
    fi
}

echo ""
echo "========================================"
echo "  TESTES AUTOMATIZADOS - ANALISADOR DNA"
echo "========================================"
echo ""

echo -e "${YELLOW}--- PARTE I: BASICO ---${NC}"

check "T04 - Listar sem cadastros" \
"2
0" \
"nenhuma"

check "T01 - Cadastrar sequencia valida" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
0" \
"sucesso"

check "T02 - Cadastrar base invalida" \
"1
Seq_X
ATGXCG
0" \
"invalida"

check "T05 - Listar com 3 sequencias" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
1
Seq_B
GCGCGCGCATATATCGCGCG
1
Seq_C
AAAATTTTAAAATTTTAAAA
2
0" \
"Seq_A"

check "T06 - Contar bases Seq_A" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
3
Seq_A
0" \
"A:.*5"

check "T07 - Contar bases Seq_B" \
"1
Seq_B
GCGCGCGCATATATCGCGCG
3
Seq_B
0" \
"G:.*[78]"

check "T08 - Contar bases Seq_C" \
"1
Seq_C
AAAATTTTAAAATTTTAAAA
3
Seq_C
0" \
"C:.*0"

check "T09 - GC de Seq_A" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
4
Seq_A
0" \
"52"

check "T10 - GC de Seq_B" \
"1
Seq_B
GCGCGCGCATATATCGCGCG
4
Seq_B
0" \
"70"

check "T11 - GC de Seq_C" \
"1
Seq_C
AAAATTTTAAAATTTTAAAA
4
Seq_C
0" \
"0.00"

check "T03 - Limite de 10 sequencias" \
"1
S1
ATGC
1
S2
ATGC
1
S3
ATGC
1
S4
ATGC
1
S5
ATGC
1
S6
ATGC
1
S7
ATGC
1
S8
ATGC
1
S9
ATGC
1
S10
ATGC
1
S11
ATGC
0" \
"limite\|maximo\|chei"

echo ""
echo -e "${YELLOW}--- PARTE II: INTERMEDIARIO ---${NC}"

check "T13 - Ordenar por tamanho" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
1
Seq_B
GCGCGCGCATATATCGCGCG
1
Seq_C
AAAATTTTAAAATTTTAAAA
5
0" \
"Seq_A"

check "T14 - Ordenar com 1 sequencia" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
5
0" \
"."

check "T15 - Buscar motif existente GAT" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
6
Seq_A
GAT
0" \
"1"

check "T16 - Buscar motif inexistente ZZZ" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
6
Seq_A
ZZZ
0" \
"0"

echo ""
echo -e "${YELLOW}--- PARTE III: AVANCADO ---${NC}"

rm -f sequencias.txt

check "T17 - Salvar sequencias em arquivo" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
1
Seq_B
GCGCGCGCATATATCGCGCG
7
0" \
"salv\|sucesso"

if [ -f sequencias.txt ]; then
    ok "T17b - Arquivo sequencias.txt foi criado"
    PASS=$((PASS+1))
else
    fail "T17b - Arquivo sequencias.txt foi criado" "arquivo existe" "arquivo nao encontrado"
fi

check "T18 - Carregar arquivo salvo" \
"8
2
0" \
"Seq_A\|carregad"

rm -f sequencias.txt

check "T19 - Carregar arquivo inexistente" \
"8
0" \
"nao encontrado\|not found\|erro"

check "T20 - Hamming Seq_A vs Seq_D (iguais)" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
1
Seq_D
ATGCCGTAACGGATTAGCC
9
Seq_A
Seq_D
0" \
"0"

check "T21 - Hamming Seq_A vs Seq_E (1 diferenca)" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
1
Seq_E
ATGCCGTAACGGATTAGCT
9
Seq_A
Seq_E
0" \
"1"

check "T22 - Hamming tamanhos diferentes" \
"1
Seq_A
ATGCCGTAACGGATTAGCC
1
Seq_B
GCGCGCGCATATATCGCGCG
9
Seq_A
Seq_B
0" \
"diferente\|incomp\|-1"

echo ""
echo "========================================"
printf "  RESULTADO: ${GREEN}%d OK${NC} | ${RED}%d FALHOU${NC}\n" $PASS $FAIL
echo "========================================"
echo ""