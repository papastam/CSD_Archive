% Fortwsh arxeiou sto MATLAB
[s, Fs] = audioread(’speech.wav’);

% 8eloume 30 ms tmhmata, se posa deigmata antistoixoun?
T = round(0.03 * Fs);

% Synolikh diarkeia shmatos
L = length(s);

% Posoi palmoi xwrane sth diarkeia L tou shmatos?
N = L/T;

% Diatre3e to shma
for i = 1:N-1
  % Kopse to katallhlo tmhma (kane xrhsh tou i kai tou T)
  windowed_speech = s((T*(i-1))+1:T*i);
  
  % Ypologise thn energeia tou tmhmatos
  Energy(i) = (1/Fs)*sum(windowed_speece^2);
  
  % Kentro tou para8yropoihmenou shmatos
  Time(i) = round(i*T)
  
end

% Katwfli apofashs (p.x.)
Number_of_Silence_Frames = round(2*Fs/T);
Threshold = mean(Energy(1:Number_of_Silence_Frames));

% Apofash
for i = 1:N-1
  if Energy(i) > Threshold
    D(i) = 1; % Voice detected
  else
    D(i) = 0; % Voice not detected
  end
end

% Grafhma
t = 0:1/Fs:(L-1)/Fs;
n = 0:L-1;
Din = interp1(Time, D, n, "linear");
plot(t, Din, "LineWidth", 4); hold on; plot(t, s/max(abs(s)), ’r’);
hold off; grid;
title(’Voice Activity Detector’); xlabel(’Time (s)’);
