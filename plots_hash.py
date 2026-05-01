import sys
import matplotlib.pyplot as plt

def create_histogram(input_file, output_file):
    indices = []
    lengths = []
    
    try:
        with open(input_file, 'r') as f:
            lines = [line.strip() for line in f.readlines() if line.strip()]
            
            if len(lines) < 3:
                return

            word_count = lines[0]
            load_factor = lines[1]

            for line in lines[2:]:
                if ':' in line:
                    parts = line.split(':')
                    indices.append(int(parts[0]))
                    lengths.append(int(parts[1]))

        # Расчет статистики
        total_buckets = len(lengths)
        avg_length = sum(lengths) / total_buckets if total_buckets > 0 else 0
        variance = sum((l - avg_length) ** 2 for l in lengths) / total_buckets if total_buckets > 0 else 0

        plt.figure(figsize=(15, 7))
        plt.bar(indices, lengths, width=5.0, color='royalblue', edgecolor='none')
        
        title_text = f"Количество бакетов: {word_count}    |    Средняя длина: {avg_length:.3f}    |    Load factor: {load_factor}    |    Дисперсия: {variance:.3f}"
        plt.title(title_text, fontsize=12, pad=15)
        
        plt.xlabel("Номер ячейки")
        plt.ylabel("Длина бакета")
        plt.grid(axis='y', linestyle=':', alpha=0.6)

        plt.xticks(range(0, max(indices) + 1, 500))
        plt.yticks(range(0, max(lengths) + 1, 10))

        plt.savefig(output_file, bbox_inches='tight')
        plt.close()
        
    except:
        pass

if __name__ == "__main__":
    if len(sys.argv) >= 3:
        create_histogram(sys.argv[1], sys.argv[2])
