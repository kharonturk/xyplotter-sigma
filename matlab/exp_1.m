howmany = 1E4; % ���� �ɸ��� for ������ ���ؼ� �̷��� �ݺ�Ƚ���� ũ�� ��ƺ��ҽ��ϴ�.
h = waitbar(0,'Please wait...'); % ���� �־ waitbar�� ���ϴ�.
%a = zeros(1,howmany) % �ʱ�ȭ
%%
for k=1:howmany; % ���� ����
%     a(k) = k^2; % ���� �� ���� ��
     waitbar(k/howmany) % ��ȣ �� ���� ������ �� ���ٴ� �ٲ�� ���ݴϴ�.
end
close(h) % ������ ������ �̰͵� �ݾ��ݴϴ�.
