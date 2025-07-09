// Simulation of a program which performs a download
//
// One thread featches the data
// Another thread displays a progress bar
// A third thread processes the data when the download is complete
//
// Implemented using a condition variabla to communicate between the threads
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <string>

using namespace std::literals;

// Shared variable for the data being fetched
std::string g_sdata;

// bool flags for predicates
bool g_update_progress = false;
bool g_completed = false;

// Mutexes to protect the shared variables
std::mutex g_data_mutex;
std::mutex g_completed_mutex;

// The condition variables
std::condition_variable g_data_cv;
std::condition_variable g_completed_cv;

// Data fetching thread
void fetch_data()
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Fetcher thread waiting for data..." << std::endl;
		std::this_thread::sleep_for(2s);

		// Update sdata, then notify the progress bar thread
		std::unique_lock<std::mutex> lock(g_data_mutex);
		g_sdata += "Block" + std::to_string(i+1);
		std::cout << "Fetched sdata: " << g_sdata << std::endl;
		g_update_progress = true;
		lock.unlock();
		g_data_cv.notify_all();
  }

	std::cout << "Fetch sdata has ended\n";

	// Tell the progress bar thread to exit
	// and wake up the processing thread
	std::lock_guard<std::mutex> lg(g_completed_mutex);
	g_completed = true;
	g_completed_cv.notify_all();
}

// Progress bar thread
void progress_bar()
{
	size_t len = 0;

	while (true) {
		std::cout << "Progress bar thread waiting for data..." << std::endl;

		// Wait until there is some new data to display
		std::unique_lock<std::mutex> lock(g_data_mutex);
		g_data_cv.wait(lock, [] { return g_update_progress; });

		// Wake up and use the new value
		len = g_sdata.size();

		// Set our flag back to false
		g_update_progress = false;
		lock.unlock();

		std::cout << "Received " << len << " bytes so far" << std::endl;

		// Check if the download has finished
		std::unique_lock<std::mutex> compl_lck(g_completed_mutex);

		// Terminate when the download has finished
		if (g_completed_cv.wait_for(compl_lck, 10ms, [] { return g_completed; })) {
			std::cout << "Progress bar thread has ended" << std::endl;
			break;
		}
	}
}

void process_data() {
	std::this_thread::sleep_for(200ms);
	std::cout << "Processing thread waiting for data..." << std::endl;

	// Wait until the download is complete
	std::unique_lock<std::mutex> lock(g_completed_mutex);   // Acquire lock

	g_completed_cv.wait(lock, [] { return g_completed; });
	lock.unlock();

	std::lock_guard<std::mutex> data_lck(g_data_mutex);
	std::cout << "Processing sdata: " << g_sdata << std::endl;

	// Process the data...
}

int main()
{
	// Start the threads
	std::thread fetcher(fetch_data);
	std::thread prog(progress_bar);
	std::thread processor(process_data);

	fetcher.join();
	prog.join();
	processor.join();

  return 0;
}