# Priority Queue with Aging

학습 목적의 Priority Queue + Aging 메커니즘 구현 (C++)

## 프로젝트 개요

이 프로젝트는 운영체제의 CPU 스케줄링에서 중요한 개념인 **Priority Queue**와 **Aging** 기법을 C++로 직접 구현한 것입니다.

### 주요 기능

- **Custom Min-Heap 구현**: `std::priority_queue`를 사용하지 않고 직접 구현
- **Aging 메커니즘**: 대기 시간에 따라 동적으로 우선순위 조정
- **Starvation 방지**: 낮은 우선순위 프로세스도 결국 실행되도록 보장
- **실시간 시각화**: 콘솔에서 스케줄링 과정 실시간 확인
- **통계 분석**: 평균 대기 시간, 반환 시간, CPU 활용률 등

## 핵심 개념

### Priority Queue (우선순위 큐)

- 각 요소가 우선순위를 가지며, 높은 우선순위를 가진 요소가 먼저 처리
- Min-Heap 기반 구현 (낮은 값 = 높은 우선순위)
- 삽입/삭제: O(log n)

### Aging 기법

**문제**: 우선순위 스케줄링의 **Starvation (기아) 문제**
- 낮은 우선순위 프로세스가 무한정 대기할 수 있음

**해결**: 대기 시간에 따라 우선순위를 점진적으로 증가

```
effective_priority = base_priority - (waiting_time × aging_factor)
```

## 프로젝트 구조

```
aging/
├── include/            # 헤더 파일
│   ├── Process.h
│   ├── PriorityQueue.h
│   ├── Scheduler.h
│   ├── Statistics.h
│   └── Visualizer.h
├── src/               # 소스 파일
│   ├── Process.cpp
│   ├── PriorityQueue.cpp
│   ├── Scheduler.cpp
│   ├── Statistics.cpp
│   └── Visualizer.cpp
├── tests/             # 테스트 파일
├── bin/               # 실행 파일
├── obj/               # 오브젝트 파일
├── main.cpp           # 메인 프로그램
├── Makefile           # 빌드 시스템
└── README.md
```

## 빌드 및 실행

### 요구사항

- C++17 이상 지원 컴파일러 (g++, clang++, MSVC)
- Make (빌드 시스템)

### 빌드

```bash
# 기본 빌드
make

# 디버그 빌드
make debug

# 릴리즈 빌드 (최적화)
make release

# 클린 빌드
make clean
make
```

### 실행

```bash
# 빌드 후 실행
make run

# 또는 직접 실행
./bin/aging_demo.exe
```

## 데모 시나리오

### Scenario 1: Aging 없음 (Starvation 발생)

```
Aging Factor: 0.0
결과: 높은 우선순위 프로세스만 실행, 낮은 우선순위는 대기
```

### Scenario 2: Aging 적용 (Starvation 방지)

```
Aging Factor: 0.1 (보수적)
결과: 대기 시간에 따라 우선순위 상승, 모든 프로세스 실행
```

### Scenario 3: 공격적 Aging

```
Aging Factor: 0.5 (공격적)
결과: 빠른 우선순위 상승, 더 균형잡힌 실행 순서
```

### Scenario 4: 랜덤 프로세스 (대규모)

```
15개의 랜덤 프로세스 생성 및 스케줄링
```

### Scenario 5: 실시간 시각화

```
단계별 실시간 시각화로 스케줄링 과정 관찰
```

### Scenario 6: Aging Factor 비교

```
여러 Aging Factor 값에 대한 성능 비교
```

## 주요 클래스

### Process

프로세스/태스크 표현

```cpp
- id: 프로세스 ID
- base_priority: 원래 우선순위
- effective_priority: Aging 적용 후 우선순위
- arrival_time: 도착 시간
- burst_time: 실행 시간
- waiting_time: 대기 시간
```

### PriorityQueue

Aging 기능이 포함된 커스텀 Min-Heap

```cpp
- insert(): 프로세스 삽입
- extractMin(): 최고 우선순위 프로세스 추출
- applyAging(): 모든 프로세스에 Aging 적용
- rebuildHeap(): Heap 속성 재구성
```

### Scheduler

시뮬레이션 오케스트레이터

```cpp
- run(): Non-preemptive 스케줄링 실행
- generateRandomProcesses(): 랜덤 프로세스 생성
- displayStatistics(): 통계 출력
- displayGanttChart(): Gantt 차트 표시
```

### Statistics

성능 메트릭 추적

```cpp
- 평균 대기 시간
- 평균 반환 시간
- 평균 응답 시간
- CPU 활용률
- Aging 이벤트 횟수
```

### Visualizer

콘솔 출력 유틸리티

```cpp
- 큐 상태 표시
- 프로세스 정보 출력
- Gantt 차트 생성
- 진행 표시
```

## 알고리즘

### Aging 적용

```cpp
for each process in heap:
    waiting_time = current_time - arrival_time - execution_time
    effective_priority = base_priority - (waiting_time × aging_factor)
    effective_priority = max(0.0, effective_priority)

rebuild_heap()  // Heap 속성 유지
```

### 스케줄러 실행 (Non-Preemptive)

```cpp
while (has_processes OR !queue.isEmpty()):
    add_arrived_processes_to_queue()

    if (!queue.isEmpty()):
        process = queue.extractMin()
        execute_process_fully()

        during_execution:
            queue.applyAging()       // 대기 프로세스 Aging
            display_queue_state()    // 시각화
    else:
        current_time++  // CPU 유휴
```

## Aging Factor 튜닝

| Aging Factor | 설명 | 특징 |
|--------------|------|------|
| 0.0 | Aging 없음 | Starvation 발생 가능 |
| 0.05 | 매우 보수적 | 느린 우선순위 상승 |
| 0.1 | 보수적 (권장) | 균형잡힌 스케줄링 |
| 0.2 | 적극적 | 빠른 우선순위 상승 |
| 0.5 | 매우 적극적 | 거의 FCFS에 가까움 |

## 학습 목표

이 프로젝트를 통해 배울 수 있는 내용:

1. **자료구조**: 커스텀 Heap 구현 및 유지보수
2. **알고리즘**: 동적 우선순위 조정, Heap 연산
3. **C++ 프로그래밍**:
   - 객체지향 설계
   - 메모리 관리 (포인터, 소멸자)
   - STL 컨테이너 활용
4. **운영체제**: CPU 스케줄링, Starvation 문제
5. **시스템 프로그래밍**: 시뮬레이션 시스템 구현
6. **소프트웨어 공학**: 모듈형 설계, 테스트

## 통계 분석 예시

```
========================================================
                STATISTICS REPORT
========================================================
Total Processes:          5
Completed Processes:      5
Total Execution Time:     20 time units
--------------------------------------------------------
Average Waiting Time:     5.40 time units
Average Turnaround Time:  8.80 time units
Average Response Time:    5.40 time units
Maximum Waiting Time:     12 time units
--------------------------------------------------------
CPU Utilization:          85.00%
Total Aging Events:       47
========================================================
```

## 확장 기능 (선택적)

추가 학습을 위한 확장 아이디어:

- [ ] Preemptive 스케줄링 (Time Quantum)
- [ ] 다양한 Aging 전략 (지수, 로그)
- [ ] Multi-level Feedback Queue
- [ ] GUI 시각화 (SFML, Qt)
- [ ] 파일 I/O (프로세스 정의 파일)
- [ ] 성능 벤치마킹 스위트
- [ ] Unit 테스트 (Google Test)

## 라이선스

학습 목적으로 자유롭게 사용 가능합니다.

## 작성자

Priority Queue + Aging 구현 (2025)
