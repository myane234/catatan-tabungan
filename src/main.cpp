#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

struct Transaksi {
    std::string tanggal;
    long long nominal;
};

struct Tabungan {
    std::string nama;
    long long saldo;
    long long target;
    std::vector<Transaksi> history;
};

std::string getTanggal() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, 20, "%d-%m-%Y/%A-%B-%y", ltm);
    return std::string(buffer);
}

void tambahTransaksi(Tabungan &tabungan, long long nominal) {
    Transaksi transaksi = {getTanggal(), nominal};
    tabungan.history.push_back(transaksi);
}

void buatTabungan(std::vector<Tabungan> &tabungans) {
    Tabungan t;
    std::cout << "Masukkan nama tabungan: ";
    std::cin.ignore();
    std::getline(std::cin, t.nama);
    t.saldo = 0;
    std::cout << "Masukkan target tabungan (atau 0 jika tidak ada target): ";
    std::cin >> t.target;
    tabungans.push_back(t);
    std::cout << "Tabungan '" << t.nama << "' berhasil dibuat.\n";
}

void tampilkanSaldo(Tabungan &tabungan) {
    std::cout << "Saldo tabungan -" << tabungan.nama << "- = Rp. " << tabungan.saldo << "\n";
    if (tabungan.target > 0) {
        std::cout << "Target tabungan = Rp. " << tabungan.target << "\n";
        if (tabungan.saldo >= tabungan.target) {
            std::cout << "Selamat! Anda telah mencapai target tabungan!\n";
        }
    }
}

void lihatHistory(const Tabungan &tabungan) {
    std::cout << "Riwayat transaksi untuk tabungan -" << tabungan.nama << "-:\n";
    for (const auto &transaksi : tabungan.history) {
        std::cout << transaksi.tanggal << ": ";
        if (transaksi.nominal > 0) {
            std::cout << "+Rp. " << transaksi.nominal << "\n";
        } else {
            std::cout << "-Rp. " << -transaksi.nominal << "\n";
        }
    }
}

void menabung(Tabungan &tabungan) {
    long long nominal;
    std::cout << "Masukkan nominal tabungan: ";
    std::cin >> nominal;
    tabungan.saldo += nominal;
    tambahTransaksi(tabungan, nominal);
    std::cout << "Berhasil menabung Rp. " << nominal << " ke tabungan '" << tabungan.nama << "'.\n";
}

void kurangiSaldo(Tabungan &tabungan) {
    long long nominal;
    std::cout << "Masukkan nominal yang ingin dikurangi dari tabungan: ";
    std::cin >> nominal;
    if (nominal > tabungan.saldo) {
        std::cout << "Saldo tidak mencukupi untuk mengurangi sebesar Rp. " << nominal << ".\n";
    } else {
        tabungan.saldo -= nominal;
        tambahTransaksi(tabungan, -nominal);
        std::cout << "Berhasil mengurangi Rp. " << nominal << " dari tabungan '" << tabungan.nama << "'.\n";
    }
}

void updateTarget(Tabungan &tabungan) {
    std::cout << "Target tabungan saat ini: Rp. " << tabungan.target << "\n";
    std::cout << "Masukkan target baru (atau 0 untuk menghapus target): ";
    std::cin >> tabungan.target;
    std::cout << "Target tabungan berhasil diperbarui.\n";
}

int main() {
    std::vector<Tabungan> tabungans;
    int pilihan;

    while (true) {
        std::cout << "\nMenu Utama:\n";
        std::cout << "1. Buat Tabungan\n";
        std::cout << "2. Pilih Tabungan\n";
        std::cout << "3. Keluar\n";
        std::cout << "Masukkan pilihan: ";
        std::cin >> pilihan;

        if (pilihan == 1) {
            buatTabungan(tabungans);
        } else if (pilihan == 2) {
            if (tabungans.empty()) {
                std::cout << "Tidak ada tabungan yang tersedia.\n";
                continue;
            }

            std::cout << "Pilih Tabungan:\n";
            for (size_t i = 0; i < tabungans.size(); ++i) {
                std::cout << i + 1 << ". " << tabungans[i].nama << "\n";
            }

            int idx;
            std::cout << "Masukkan nomor tabungan: ";
            std::cin >> idx;

            if (idx < 1 || idx > tabungans.size()) {
                std::cout << "Pilihan tidak valid.\n";
                continue;
            }

            Tabungan &tabungan = tabungans[idx - 1];
            int subPilihan;
            while (true) {
                tampilkanSaldo(tabungan);
                std::cout << "\n1. Lihat History\n";
                std::cout << "2. Menabung\n";
                std::cout << "3. Kurangi Saldo\n";
                std::cout << "4. Update Target\n";
                std::cout << "5. Kembali ke Menu Utama\n";
                std::cout << "Masukkan pilihan: ";
                std::cin >> subPilihan;

                if (subPilihan == 1) {
                    lihatHistory(tabungan);
                } else if (subPilihan == 2) {
                    menabung(tabungan);
                } else if (subPilihan == 3) {
                    kurangiSaldo(tabungan);
                } else if (subPilihan == 4) {
                    updateTarget(tabungan);
                } else if (subPilihan == 5) {
                    break;
                } else {
                    std::cout << "Pilihan tidak valid.\n";
                }
            }
        } else if (pilihan == 3) {
            std::cout << "Terima kasih telah menggunakan program ini.\n";
            break;
        } else {
            std::cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
