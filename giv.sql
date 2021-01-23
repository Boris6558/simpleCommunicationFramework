/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 80018
Source Host           : localhost:3306
Source Database       : giv

Target Server Type    : MYSQL
Target Server Version : 80018
File Encoding         : 65001

Date: 2021-01-23 19:31:11
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for generated_user_id
-- ----------------------------
DROP TABLE IF EXISTS `generated_user_id`;
CREATE TABLE `generated_user_id` (
  `user_id` int(11) NOT NULL DEFAULT '0',
  `offset` int(11) NOT NULL DEFAULT '0',
  `user_name` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '',
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of generated_user_id
-- ----------------------------
INSERT INTO `generated_user_id` VALUES ('755451', '14', 'start_id');
INSERT INTO `generated_user_id` VALUES ('755452', '0', 'bin');
INSERT INTO `generated_user_id` VALUES ('755453', '0', 're');
INSERT INTO `generated_user_id` VALUES ('755454', '0', 'fsef');
INSERT INTO `generated_user_id` VALUES ('755455', '0', 'fseg');
INSERT INTO `generated_user_id` VALUES ('755456', '0', 'cs');
INSERT INTO `generated_user_id` VALUES ('755457', '0', 'fse');
INSERT INTO `generated_user_id` VALUES ('755458', '0', 'fff');
INSERT INTO `generated_user_id` VALUES ('755459', '0', 'gtr');
INSERT INTO `generated_user_id` VALUES ('755460', '0', 'grdh');
INSERT INTO `generated_user_id` VALUES ('755461', '0', 'sdf');
INSERT INTO `generated_user_id` VALUES ('755462', '0', 'fcesgf');
INSERT INTO `generated_user_id` VALUES ('755463', '0', 'fes');
INSERT INTO `generated_user_id` VALUES ('755464', '0', 'fe');

-- ----------------------------
-- Table structure for user_info
-- ----------------------------
DROP TABLE IF EXISTS `user_info`;
CREATE TABLE `user_info` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL DEFAULT '0',
  `user_data` varbinary(512) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`,`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=gb2312;

-- ----------------------------
-- Records of user_info
-- ----------------------------
INSERT INTO `user_info` VALUES ('8', '111', '');
