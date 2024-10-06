# DuckDB

- in-memory mode
  - InMemoryBlockManager
- on disk
  - SingleFileBlockManager

## SingleFile

1. MainHeader (4KB)
   - magic number
   - version number
   - flags
2. DatabaseHeader_0, DatabaseHeader_1 (2 \* 4KB)
   - meta_block id
3. MetaBlock
   - next_block_id (8 bytes)
   - MetaBlockReader/MetaBlockWriter
   - Schema MetaBlock
   - TableData MetaBlock
4. DataBlock

- FILE_HEADER_SIZE = 4096u
- BLOCK_ALLOC_SIZE = 256KB
- CheckpointManager::ReadSchema
- void CheckpointManager::ReadTable(ClientContext &context, MetaBlockReader &reader)
- Row-Group Based Storage