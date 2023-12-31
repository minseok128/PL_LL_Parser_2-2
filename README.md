# Principles of programming languages <Assignment 1>

<p align="center">
   <img src="./test_case/img_src/image001.png" width="500px"/>
</p>

**20203361 장민석**

[View on GitHub](https://github.com/minseok128/PL_Parser_2-2)

## GOAL

다음의 LL문법 BNF를 따르는 Input file에 대해서 LL 파싱을 수행하고, 그 결과를 출력한다.

```
<program> → <statements>
<statements>→ <statement> | <statement><semi_colon><statements>
<statement> → <ident><assignment_op><expression>
<expression> → <term><term_tail>
<term_tail> → <add_op><term><term_tail> | ε
<term> → <factor> <factor_tail>
<factor_tail> → <mult_op><factor><factor_tail> | ε
<factor> → <left_paren><expression><right_paren> | <ident> | <const>
<const> → any decimal numbers
<ident> → any names conforming to C identifier rules
<assignment_op> → :=
<semi_colon> → ;
<add_operator> → + | -
<mult_operator> → * | /
<left_paren> → (
<right_paren> → )
```

## Environment

```
개발 및 실행 환경: macOS Ventura 13.1(22C65) Apple M1

언어: c++

컴파일러: clang version 14.0.0 (clang-1400.0.29.202)

타겟: arm64-apple-darwin22.2.0
```

## HOW TO

```bash
$ make
$ ./parser test_case/test1.txt
# or
$ make test
```

<img src="./test_case/img_src/image016.png" width="850px"/>


---

## 구현 세부 사항

### 1-1. 구현 세부 사항 결정: <span style="color:yellow;">WARNING 처리</span>

이 프로그램은 코드의 일부분이 누락되거나 부적절하게 작성되었을 때 경고 메시지를 통해 사용자에게
알리고 가능한 경우 자동으로 코드를 수정하여 의미 있는 문장으로 변환할 수 있다. 다음은 10가지 유
형의 경고와 그에 따른 수정 사항이다.

1. **중복 연산자 (경고_0)**: 하나 이상의 연산자가 연속적으로 사용된 경우이다. 예를 들어
   "operand2 := operand1 + + - 2;"에서 '+' 연산자가 중복된다. 이 때 첫 번째 연산자를 제외한 나머지
   를 제거하여 문장을 정정하고 정상화한다.
    ```
    operand1 := 3;
    operand2 := operand1 + + -/ 2;
    target := operand1 + operand2 * 3
    ```
   <img src="./test_case/img_src/image002.png" width="700px"/>

2. **닫는 괄호 누락 (경고_1)**: 열린 괄호에 비해 닫는 괄호가 부족한 경우이다. 해당 문장의 마지막에
   도달했을 때 부족한 닫는 괄호의 수에 맞게 적절하게 닫는 괄호를 추가하여 괄호의 쌍을 완성하여 정
   상화한다.
    ```
    operand1 := (3 * (3 - 1) * (5 - 3;
    target := operand1 * ((1) - (((2 
    ```
   <img src="./test_case/img_src/image003.png" width="700px"/>

3. **불필요한 <factor> 요소 (경고_2)**: <factor> 구문 뒤에 예상치 못한 요소가 나타난 경우이다. 이 불
   필요한 요소들을 모두 제거하여 문장을 정상화한다.
    ```
    operand1 := 3 21 3 + (2 321 * 2) 132 operand1;
    operand2 := operand1 operand1 operand2+ operand1 123 operand2 operand1;
    target := operand1 1 2
    ```
   <img src="./test_case/img_src/image004.png" width="700px"/>

4. **대입 연산자 누락 (경고_3)**: 대입 연산자가 없는 경우에는 필요한 위치에 추가하여 문장을 정상화한
   다.
    ```
    operand1 3;
    operand2 := operand1 + 2;
    target operand1 + operand2 * 3
    ```
   <img src="./test_case/img_src/image005.png" width="700px"/>

5. **정의되지 않은 토큰 (경고_4)**: 문장 내에 정의될 수 없는 문자열이 발견되어 의미 있는 토큰으로 변
   환 할 수 없는 상황이 발견되면 해당 토큰을 제거하고 문장을 정상화한다.
    ```
    operand1 := &%3 ^^;$#
    operand2 := operand1 &$ + &$2 
    ```
   <img src="./test_case/img_src/image006.png" width="700px"/>

6. **피연산자 부족 (경고_5)**: 연산자에 짝이 맞도록 필요한 피연산자가 없는 경우 누락된 위치에 정의
   되지 않은 가상의 값을 추가하여 문장을 정상화한다.
    ```
    operand1 := 3 - ;
    operand2 := * 2 + (1 - 2);
    target :=
    ```
   <img src="./test_case/img_src/image007.png" width="700px"/>

7. **숫자가 아닌 문자 포함 (경고_6)**: 숫자로만 이루어져야 하는 상수에 숫자 외의 다른 문자가 포함된
   경우 해당 문자를 제거하여 정상적인 숫자가 될 수 있도록 복구한다.
    ```
    operand1 := 1%1^1@1#;
    operand2 := operand1 + 2!!@#
    ```
   <img src="./test_case/img_src/image008.png" width="700px"/>

8. **변수명에 부적절한 문자 포함 (경고_7)**: 변수명에 허용되지 않는 문자가 포함된 경우 이러한 문자
   들을 모두 제거하여 규칙에 맞는 변수명이 될 수 있도록 복구한다.
    ```
    op%^er$@and1 := 3;
    op@era#n%d2 := op^^er^^and1 + 2;
    tar^^$#%get := o^pe^rand^1 + operand2^ 
    ```
   <img src="./test_case/img_src/image009.png" width="700px"/>

9. **여는 괄호 누락 (경고_8)**: 여는 괄호가 닫는 괄호보다 적을 경우 여는 괄호를 적절히 넣을 수 없으
   므로 현재 등장한 짝이 맞지 않는 닫는 괄호를 모두 제거하여 문장을 정상화한다.
    ```
    operand1 := 2 + 3) * 2;
    operand2 := operand1) ))+ ((2))))
    ```
   <img src="./test_case/img_src/image010.png" width="700px"/>

10. **대입 연산자 중복 (경고_9)**: 한 문장 내에서 대입 연산자가 여러 번 사용된 경우 BNF 상으로 올바
    른 위치에 있는 하나의 대입 연산자만을 남기고 나머지는 모두 제거한다.
    ```
    operand1 := 3 := := := + 1 := := - 3;
    operand2 := := := operand1 := + 2;
    target := operand1 + operand2 * 3 := 
    ```
    <img src="./test_case/img_src/image011.png" width="700px"/>

### 1-2. 구현 세부 사항 결정: <span style="color:red;">ERROR 처리</span>

이 프로그램은 특정 문장을 최선으로 복구해도 유의미한 문장을 구성할 수 없는 경우 ERROR로 판정
하였다. 다음은 3가지 유형의 경고와 그에 따른 수정 사항이다.

1. **프로그램 내에서 선언되지 않은 변수가 사용될 경우 (오류 유형 0)**: 실행 중인 프로그램에서 미리
   선언하지 않은 변수가 사용되면 이는 오류로 간주된다.
    ```
    operand2 := operand1 + 2;
    target := operand3 + operand2 * 3
    ```
   <img src="./test_case/img_src/image012.png" width="700px"/>

2. **대입 연산의 왼쪽에 변수가 없는 경우 (오류 유형 1)**: 대입 연산자의 왼쪽 부분에 변수가 존재하지
   않으면 이는 문법적으로 잘못된 것으로 오류로 분류된다. 예를 들어 ":= 1 + 2;" 또는 "2 := 1 * 3;" 같
   은 구문은 왼쪽 항이 빠져 있다. 이 경우 LHS에 임시 값을 지정해 놓고 무의미한 문장을 실행한다.
    ```
    := 1 + 2;
    2 := 1 * 3
    ```
   <img src="./test_case/img_src/image013.png" width="700px"/>

3. **0으로 나누기 시도 (오류 유형 2)**: 프로그래밍에서 0으로 나누는 것은 정의되지 않은 연산으로 문
   장 내에서 이를 시도할 경우 즉시 오류로 분류한다. "operand1 := 21 / 0 + 1;" 같은 예에서 볼 수 있듯
   0으로 나누기 시도는 오류로 간주된다.
    ```
    operand1 := 21 / 0 + 1;
    operand2 := 2 / operand1 
    ```
   <img src="./test_case/img_src/image014.png" width="700px"/>

### 1-3. 구현 세부 사항 결정: <span style="color:green;">-v option</span>

**-v 옵션**이 argv[1]에 제공된 경우 기존의 토큰의 문자열을 출력하는 부분에서 문자열이 아닌
토큰의 타입을 출력하는 방식으로 구현하였다.

```
operand1 := 3;
operand2 := operand1 + 2;
target := operand1 + operand2 * 3
```

<img src="./test_case/img_src/image015.png" width="700px"/>

## TO DO

- [X] 에러 계속 찾기

- [X] 보고서 작성

- [X] '-v' option 설계 및 개발

- [X] 애플 실리콘 환경 빌드 테스트
