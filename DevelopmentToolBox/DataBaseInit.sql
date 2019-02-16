DROP TABLE IF EXISTS "DirectoryList";
CREATE TABLE "DirectoryList" (
  "DirectoryPath" TEXT NOT NULL,
  PRIMARY KEY ("DirectoryPath")
);
DROP TABLE IF EXISTS "FileIndex";
CREATE TABLE "FileIndex" (
  "IndexKey" TEXT NOT NULL,
  "Name" TEXT,
  "Path" TEXT,
  "Size" integer,
  "Type" TEXT,
  "CreationTime" integer,
  "ChangeTime" integer,
  "InterviewTime" integer,
  PRIMARY KEY ("IndexKey")
);
DROP TABLE IF EXISTS "ShortcutPath";
CREATE TABLE "ShortcutPath" (
  "ToolBtnObjName" TEXT,
  "TagPath" TEXT
);
DROP TABLE IF EXISTS "TaskList";
CREATE TABLE "TaskList" (
  "ID" text NOT NULL,
  "Name" text,
  "Content" text,
  "TaskState" text,
  "CreateTime" integer,
  "StartTime" integer,
  "EndTime" integer,
  "isDelete" integer,
  "DeleteTime" integer,
  PRIMARY KEY ("ID")
);
DROP TABLE IF EXISTS "WorkLog";
CREATE TABLE "WorkLog" (
  "Time" TEXT,
  "Content" TEXT
);
