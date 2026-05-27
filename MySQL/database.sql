-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               12.2.2-MariaDB - MariaDB Server
-- Server OS:                    Win64
-- HeidiSQL Version:             12.16.0.7229
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

-- Dumping structure for table engkqopenmp.bans
CREATE TABLE IF NOT EXISTS `bans` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(24) NOT NULL,
  `ucp` varchar(24) NOT NULL,
  `admin` varchar(24) NOT NULL,
  `adminname` varchar(32) NOT NULL,
  `reason` varchar(128) NOT NULL,
  `ban_date` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `ucp` (`ucp`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping structure for table engkqopenmp.doors
CREATE TABLE IF NOT EXISTS `doors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) DEFAULT 'None',
  `password` varchar(50) DEFAULT '',
  `icon` int(11) DEFAULT 19130,
  `locked` int(11) NOT NULL DEFAULT 0,
  `admin` int(11) NOT NULL DEFAULT 0,
  `vip` int(11) NOT NULL DEFAULT 0,
  `faction` int(11) NOT NULL DEFAULT 0,
  `family` int(11) NOT NULL DEFAULT -1,
  `garage` tinyint(3) NOT NULL DEFAULT 0,
  `custom` int(11) NOT NULL DEFAULT 0,
  `extvw` int(11) DEFAULT 0,
  `extint` int(11) DEFAULT 0,
  `extposx` float DEFAULT 0,
  `extposy` float DEFAULT 0,
  `extposz` float DEFAULT 0,
  `extposa` float DEFAULT 0,
  `intvw` int(11) DEFAULT 0,
  `intint` int(11) NOT NULL DEFAULT 0,
  `intposx` float DEFAULT 0,
  `intposy` float DEFAULT 0,
  `intposz` float DEFAULT 0,
  `intposa` float DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping structure for table engkqopenmp.player
CREATE TABLE IF NOT EXISTS `player` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `username` varchar(24) NOT NULL,
  `ucp` varchar(24) NOT NULL,
  `birth_day` tinyint(4) NOT NULL DEFAULT 0,
  `birth_month` tinyint(4) NOT NULL DEFAULT 0,
  `birth_year` smallint(6) NOT NULL DEFAULT 0,
  `gender` tinyint(4) NOT NULL DEFAULT 0,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `pos_a` float NOT NULL,
  `interior` tinyint(4) NOT NULL,
  `virtual_world` int(11) NOT NULL DEFAULT 0,
  `skin` smallint(6) NOT NULL,
  `money` int(11) NOT NULL DEFAULT 0,
  `level` smallint(6) NOT NULL DEFAULT 0,
  `last_exit` int(11) NOT NULL DEFAULT 0,
  `weight` int(11) NOT NULL DEFAULT 0,
  `height` int(11) NOT NULL DEFAULT 0,
  `origin` varchar(32) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping structure for table engkqopenmp.ucp
CREATE TABLE IF NOT EXISTS `ucp` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ucp_name` varchar(24) NOT NULL,
  `password` varchar(128) NOT NULL,
  `activation` tinyint(4) NOT NULL DEFAULT 0,
  `char_slots` int(11) NOT NULL DEFAULT 1,
  `admin` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ucp_name` (`ucp_name`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping structure for table engkqopenmp.vehicles
CREATE TABLE IF NOT EXISTS `vehicles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `owner_id` int(11) NOT NULL,
  `model` smallint(6) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `pos_a` float NOT NULL,
  `color1` smallint(6) NOT NULL,
  `color2` smallint(6) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- Dumping structure for table engkqopenmp.whitelist
CREATE TABLE IF NOT EXISTS `whitelist` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ucp_name` varchar(24) NOT NULL,
  `verifycode` int(11) NOT NULL DEFAULT 0,
  `active` tinyint(4) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ucp_name` (`ucp_name`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
