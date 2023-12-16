# C-BlackJack
<img src="https://capsule-render.vercel.app/api?type=waving&color=auto&height=200&section=header&text=C-BlackJack&fontSize=90" />
	<div align="center">
	<img src="https://img.shields.io/badge/C-007396?style=flat&logo=C&logoColor=white" />

</div>

# 블랙잭 게임 프로젝트

이 프로젝트는 텍스트 기반의 블랙잭 게임을 구현한 것입니다.

## 실행 화면
<p align="center">
  <img src="https://github.com/taeksin/C-BlackJack/assets/90402009/1e914c1a-f5f0-4e12-bf62-cd07667d8632">
</p>

<p align="center">
  <img src="https://github.com/taeksin/C-BlackJack/assets/90402009/58c7440e-7eef-4321-9544-7bbe5416bd8b">
</p>

<p align="center">
  <img src="https://github.com/taeksin/C-BlackJack/assets/90402009/39ba27d2-bbcb-4b30-8ef5-9cac8909e3ec">
</p>

## 게임 설명

블랙잭은 플레이어와 딜러가 카드를 받아서 합이 21에 가까운 사람이 이기는 게임입니다. A는 1 또는 11로 선택할 수 있으며, J, Q, K는 각각 10점으로 계산됩니다.

## 사용 기술

이 게임은 C 언어로 작성되었으며, 기본적인 콘솔 환경에서 실행됩니다.

## 게임 실행

프로젝트를 클론하고, 컴파일하여 실행할 수 있습니다.

    ```bash
    gcc blackjack.c -o blackjack
    ./blackjack

1.초기 카드 나눠주기:
<li>플레이어와 딜러에게 각각 2장의 카드를 나눠줍니다.

2.블랙잭 확인:
<li>처음 받은 2장이 블랙잭인 경우에 대한 처리를 합니다.

3.플레이어 턴:
<li>HIT(카드 추가) 또는 STAY(그만 받기)를 선택할 수 있습니다.
<li>A카드는 1 또는 11로 선택이 가능하며, 플레이어가 선택할 수 있습니다.

4.딜러 턴:
<li>딜러는 17 이상이 될 때까지 카드를 더 받습니다.

5.승부 결정:
<li>최종적으로 승부를 판단하고, 결과에 따라 배팅금을 계산합니다.

## 화면 출력
gotoxy() 함수를 사용하여 화면상의 특정 위치로 이동하고, printf()로 내용을 출력합니다.
색상은 textcolor() 함수로 변경할 수 있습니다.

## 게임 메뉴
게임의 시작, 게임 설명, 종료를 선택할 수 있는 메뉴가 있습니다.
사용자의 선택에 따라 각각의 함수가 호출되어 게임이 진행됩니다.

## 기타 함수
showCursor(): 화면에서 커서를 보이게 합니다.
removeCursor(): 화면에서 커서를 감춥니다.

## 키보드 입력 처리
kbhit() 함수와 getch() 함수를 사용하여 키보드 입력을 처리합니다.
특정 키에 따라 플레이어의 선택이나 게임의 흐름이 변경됩니다.

