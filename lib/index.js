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
const getConnection = () => __awaiter(void 0, void 0, void 0, function* () {
    const relays = (0, relays_1.getRelays)();
    const ndk = new ndk_1.default({ explicitRelayUrls: relays });
    yield ndk.connect();
    return ndk;
});
const main = () => __awaiter(void 0, void 0, void 0, function* () {
    const Nostr = yield getConnection();
    console.log("connected");
    const hexPubkey = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27";
    const events = yield Nostr.fetchEvent({ authors: [hexPubkey], kinds: [0, 1], limit: 10 });
    console.log("events results:", events);
});
(() => __awaiter(void 0, void 0, void 0, function* () {
    yield main();
    return;
}))();
