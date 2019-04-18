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