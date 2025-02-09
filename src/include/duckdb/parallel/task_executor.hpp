//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/parallel/task_executor.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/atomic.hpp"
#include "duckdb/common/common.hpp"
#include "duckdb/execution/task_error_manager.hpp"
#include "duckdb/parallel/task.hpp"

namespace duckdb {
class TaskScheduler;

//! The TaskExecutor is a helper class that enables parallel scheduling and execution of tasks
// TaskExecutor 是辅助函数用来实现parallel 调度的
class TaskExecutor {
public:
	explicit TaskExecutor(ClientContext &context);
	explicit TaskExecutor(TaskScheduler &scheduler);
	~TaskExecutor();

	//! Push an error into the TaskExecutor
	void PushError(ErrorData error);
	//! Whether or not any task has encountered an error
	bool HasError();
	//! Throw an error that was encountered during execution (if HasError() is true)
	void ThrowError();

	//! Schedule a new task
	void ScheduleTask(unique_ptr<Task> task);
	//! Label a task as finished
	void FinishTask();

	//! Work on tasks until all tasks are finished. Throws an exception if any error occurred while executing the tasks.
	void WorkOnTasks();

	//! Get a task - returns true if a task was found
	bool GetTask(shared_ptr<Task> &task);

private:
	TaskScheduler &scheduler;
	TaskErrorManager error_manager;
	unique_ptr<ProducerToken> token;
	atomic<idx_t> completed_tasks;
	atomic<idx_t> total_tasks;
};

// - UnionByReaderTask
// - BaseCheckpointTask
class BaseExecutorTask : public Task {
public:
	explicit BaseExecutorTask(TaskExecutor &executor);

	// ExecuteTask是一个抽象方法 用来给其他人实现的
	virtual void ExecuteTask() = 0;
	TaskExecutionResult Execute(TaskExecutionMode mode) override;

protected:
	TaskExecutor &executor;
};

} // namespace duckdb
