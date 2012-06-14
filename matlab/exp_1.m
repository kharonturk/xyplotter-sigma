howmany = 1E4; % 오래 걸리는 for 루프를 위해서 이렇게 반복횟수를 크게 잡아보았습니다.
h = waitbar(0,'Please wait...'); % 제목 넣어서 waitbar를 띄웁니다.
%a = zeros(1,howmany) % 초기화
%%
for k=1:howmany; % 루프 시작
%     a(k) = k^2; % 루프 속 연산 예
     waitbar(k/howmany) % 괄호 속 값이 루프를 돌 때바다 바뀌게 해줍니다.
end
close(h) % 루프가 끝나면 이것도 닫아줍니다.
