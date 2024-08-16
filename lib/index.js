"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const relays_1 = require("./src/relays");
const ndk_1 = __importDefault(require("@nostr-dev-kit/ndk"));
function getConnection() {
    return __awaiter(this, void 0, void 0, function* () {
        const relays = (0, relays_1.getRelays)();
        const ndk = new ndk_1.default({ explicitRelayUrls: relays });
        yield ndk.connect();
        return ndk;
    });
}
function main() {
    return __awaiter(this, void 0, void 0, function* () {
        const Nostr = yield getConnection();
        const npub = "1739d937dc8c0c7370aa27585938c119e25c41f6c441a5d34c6d38503e3136ef";
        const events = yield Nostr.fetchEvent({ authors: [npub], kinds: [3], limit: 1 });
        console.log("events results:", events);
    });
}
main();
