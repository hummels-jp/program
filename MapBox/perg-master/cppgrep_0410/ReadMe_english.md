

### **Main Features:**

- **Command-line argument handling**: Accept a query string (`query`) and a directory path as input.
- **Recursive directory traversal**.
- **Parallel file processing**.
- **Case-insensitive search**: Enabled with the `-i` option.
- **Regular expression search**: Enabled with the `-r` option.
- **Help information**: Displayed with the `-h` option.
- **Thread-safe task queue**.



### **General Idea of the Program:**
- Create multiple worker threads to search file contents in parallel.
- Use a thread-safe task queue to distribute file search tasks.
- The main thread is responsible for traversing the directory, while the worker threads handle searching the file contents.

- Each worker thread loops to retrieve file paths from the queue until the queue is empty and has been marked as finished.
- For each file, it opens and reads the content line by line.
- Binary file detection: check each line for non-printable characters; if any are found, skip the file.
- Use `line.find(query)` to search for text matches.

